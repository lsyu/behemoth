/*
 * Labs4Physics - visualisation of physics process
 * Copyright (C) 2013  Leyko Sergey powt81lsyu@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "application.h"
#include "painter.h"

#include "core/ogl/shader.h"
#include "core/ogl/vertexbufferobject.h"

#include "core/algorithm/algostring.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_opengl.h"

#include <iostream>
#include <chrono>

namespace Core {

std::shared_ptr<Application> Application::instance = nullptr;

Application* Application::getInstance()
{
    if (!instance)
        instance = std::shared_ptr<Application>(new Application);
    return instance.get();
}

Application::Application()
    : title("Unknown"), fullScreen(false), position(0,0), size(640,480),
      depth(EApplication::ColorDepth32), timer_step_sec(1. / 60.),
      display(nullptr), queue(nullptr), timer(nullptr),
      isTimer(false), isKeyboard(false), isMouse(false),
      isTouch(false), isDisplay(false), isInit(false), secOfLastFrame(0)
{
}

Application::~Application()
{
}

void Application::clear()
{
    if (timer)
        al_destroy_timer(timer);

    if (display)
        al_destroy_display(display);

    if (queue)
        al_destroy_event_queue(queue);

//    al_shutdown_font_addon();
//    al_shutdown_ttf_addon();
//    al_shutdown_image_addon();
}

void Application::setWindowTitle(const std::string &title)
{
    this->title = title;
}

std::string Application::getWindowTitle() const
{
    return title;
}

void Application::setFullScreen(bool fullScreen)
{
    this->fullScreen = fullScreen;
}

bool Application::isFullScreen() const
{
    return fullScreen;
}

void Application::setPosition(const glm::ivec2 &position)
{
    this->position = position;
}

glm::ivec2 Application::getPosition() const
{
    return position;
}

void Application::setSize(const glm::ivec2 &size)
{
    this->size = size;
}

glm::ivec2 Application::getSize() const
{
    return size;
}

void Application::setColorDepth(EApplication::ColorDepth depth)
{
    this->depth = depth;
}

EApplication::ColorDepth Application::getColorDepth() const
{
    return depth;
}

void Application::setTimerStep(double sec)
{
    this->timer_step_sec = sec;
}

double Application::getTimerStep() const
{
    return timer_step_sec;
}

std::string Application::getOpenGLInfo() const
{
    std::string ret;
    if (al_get_opengl_variant() == 0)
        ret = "DESKTOP OPENGL: ";
    else
        ret = "OPENGL ES: ";

    std::string version = Algorithm::Str::intToHexString(al_get_opengl_version());
    version[1] = '.';
    version.resize(4);
    ret += version;

    return ret;
}

std::string Application::getOpenGLExtensions() const
{
    return std::string(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)));
}

std::vector<std::string> Application::getOpenGLExtensionsAsVec() const
{
    return Algorithm::Str::split(getOpenGLExtensions(), ' ');
}

bool Application::prepareDisplay()
{
    al_set_new_display_flags(ALLEGRO_OPENGL_3_0 | ALLEGRO_OPENGL_FORWARD_COMPATIBLE);
    al_set_new_display_option(ALLEGRO_DEPTH_SIZE, static_cast<int>(depth), ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST); // 2, 4, 8, 16

    if (fullScreen) {
        ALLEGRO_DISPLAY_MODE disp_data;
        al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
        display = al_create_display(disp_data.width, disp_data.height);
        return true;
    } else {
        al_set_new_display_flags(ALLEGRO_WINDOWED);
        display = al_create_display(size.x, size.y);
        if (display) {
            al_set_window_position(display, position.x, position.y);
            al_set_window_title(display, title.c_str());
            return true;
        }
    }
    return false;
}

bool Application::prepareTimer()
{
    // by default FPS = 60
    timer = al_create_timer(timer_step_sec);
    if (timer)
        return true;
    return false;
}

bool Application::prepareKeyboard()
{
    return al_install_keyboard();
}

bool Application::prepareMouse()
{
    return al_install_mouse();
}

bool Application::prepareTouch()
{
    return al_install_touch_input();
}

void Application::prepareEventQueue()
{
    queue = al_create_event_queue();

    if (prepareKeyboard())
        al_register_event_source(queue, al_get_keyboard_event_source());

    if (prepareMouse())
        al_register_event_source(queue, al_get_mouse_event_source());

    if (prepareTouch())
        al_register_event_source(queue, al_get_touch_input_event_source());

    if (prepareDisplay())
        al_register_event_source(queue, al_get_display_event_source(display));

    if (prepareTimer())
        al_register_event_source(queue, al_get_timer_event_source(timer));
}

bool Application::init()
{
    if (!al_init()) {
        isInit = false;
        return false;
    }

//    al_init_image_addon();
//    al_init_font_addon();
//    al_init_ttf_addon();

    bool ret = isTimer = prepareTimer();

    isKeyboard = prepareKeyboard();
    isMouse = prepareMouse();
    isTouch = prepareTouch();

    //  если таймер завелся и есть хотя бы одно утройство ввода.
    ret = ret && (isKeyboard || isMouse || isTouch);
    if (!ret) {
        isInit = false;
        return false;
    }

    isDisplay = prepareDisplay();
    if (!isDisplay) {
        isInit = false;
        return false;
    }

    prepareEventQueue();

    isInit = true;
    return true;
}

void Application::exec()
{
    using namespace std::chrono;
    if (isInit && painter) {
        prepareGL();
        ALLEGRO_EVENT event;
        bool haveNextEvent = false;
        bool repeat = true;
        while(true) {
            high_resolution_clock::time_point t1 = high_resolution_clock::now();

            haveNextEvent = al_get_next_event(queue, &event);
            if (haveNextEvent)
                repeat = updateGL(&event);
            else
                repeat = updateGL(nullptr);

            if (repeat)
                paintGL();
            else
                break;

            al_wait_for_vsync();
            al_flip_display();

            high_resolution_clock::time_point t2 = high_resolution_clock::now();

            duration<float> time_span = duration_cast< duration<double> >(t2 - t1);
            secOfLastFrame = time_span.count();
        }
    }
}

void Application::setScene(Painter *painter)
{
    this->painter = painter;
}

void Application::prepareGL()
{
    painter->prepareGL();
}

bool Application::updateGL(ALLEGRO_EVENT *e)
{
    return painter->updateGL(e);
}

void Application::paintGL()
{
    painter->paintGL();
}

} // namespace Core
