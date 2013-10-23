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
#include "abstractscene.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_opengl.h"
#include "core/ogl/shader.h"
#include "core/ogl/vertexbufferobject.h"

#include "core/algorithm/algostring.h"

#include "core/manager/resourcemanager.h"

#include <iostream>
#include <chrono>

namespace core {

CApplication *CApplication::instance = nullptr;

class __CApplicationImplDel {
public:
    explicit __CApplicationImplDel(CApplication *app) : app(app) {}
    ~__CApplicationImplDel() {delete app;}
private:
    CApplication *app;
};

CApplication* CApplication::getInstance()
{
    if (!instance) {
        instance = new CApplication;
        static __CApplicationImplDel delHelper(instance);
    }
    return instance;
}

CApplication::CApplication()
    : title("Unknown"), fullScreen(false), position(0,0), size(640,480),
      depth(ColorDepth::_32), display(nullptr), queue(nullptr), timer(nullptr), painter(),
      isTimerInitialized(false), isKeyboardInitialized(false), isMouseInitialized(false),
      isTouchInitialized(false), isDisplayInitialized(false), isInitialized(false), secOfLastFrame(0)
{
    // Инициализация ресурсов.
    CResourceManager::getInstance();
}

CApplication::~CApplication()
{
}

void CApplication::clear()
{
    if (timer)
        al_destroy_timer(timer);

    if (display)
        al_destroy_display(display);

    if (queue)
        al_destroy_event_queue(queue);
}

void CApplication::setWindowTitle(const std::string &title)
{
    this->title = title;
}

std::string CApplication::getWindowTitle() const
{
    return title;
}

void CApplication::setFullScreen(bool fullScreen)
{
    this->fullScreen = fullScreen;
}

bool CApplication::isFullScreen() const
{
    return fullScreen;
}

void CApplication::setPosition(const glm::ivec2 &position)
{
    this->position = position;
}

glm::ivec2 CApplication::getPosition() const
{
    return position;
}

void CApplication::setSize(const glm::ivec2 &size)
{
    this->size = size;
}

glm::ivec2 CApplication::getSize() const
{
    return size;
}

void CApplication::setColorDepth(ColorDepth depth)
{
    this->depth = depth;
}

ColorDepth CApplication::getColorDepth() const
{
    return depth;
}

std::string CApplication::getOpenGLInfo() const
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

std::string CApplication::getOpenGLExtensions() const
{
    return std::string(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)));
}

std::vector<std::string> CApplication::getOpenGLExtensionsAsVec() const
{
    return Algorithm::Str::split(getOpenGLExtensions(), ' ');
}

bool CApplication::prepareDisplay()
{
    al_set_new_display_flags(ALLEGRO_OPENGL_3_0 | ALLEGRO_OPENGL_FORWARD_COMPATIBLE);
    al_set_new_display_option(ALLEGRO_DEPTH_SIZE, static_cast<int>(depth), ALLEGRO_SUGGEST);

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

bool CApplication::prepareTimer()
{
    // TODO: Подумать, нужен ли вообще таймер
    timer = al_create_timer( 1.0 / 60.0 );
    if (timer)
        return true;
    return false;
}

bool CApplication::prepareKeyboard()
{
    return al_install_keyboard();
}

bool CApplication::prepareMouse()
{
    return al_install_mouse();
}

bool CApplication::prepareTouch()
{
    return al_install_touch_input();
}

void CApplication::prepareEventQueue()
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

bool CApplication::init()
{
    if (!al_init()) {
        isInitialized = false;
        return false;
    }

    bool ret = isTimerInitialized = prepareTimer();

    isKeyboardInitialized = prepareKeyboard();
    isMouseInitialized = prepareMouse();
    isTouchInitialized = prepareTouch();

    //  если таймер завелся и есть хотя бы одно утройство ввода.
    ret = ret && (isKeyboardInitialized || isMouseInitialized || isTouchInitialized);
    if (!ret) {
        isInitialized = false;
        return false;
    }

    isDisplayInitialized = prepareDisplay();
    if (!isDisplayInitialized) {
        isInitialized = false;
        return false;
    }

    prepareEventQueue();

    isInitialized = true;
    return true;
}

void CApplication::exec()
{
    using namespace std::chrono;
    if (isInitialized && painter) {
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
            std::cout << secOfLastFrame << "\n";
        }
    }
}

void CApplication::setScene(AbstractScene *painter)
{
    this->painter = painter;
}

void CApplication::prepareGL()
{
    painter->prepareGL();
}

bool CApplication::updateGL(ALLEGRO_EVENT *e)
{
    return painter->updateGL(e);
}

void CApplication::paintGL()
{
    painter->paintGL();
}

} // namespace Core
