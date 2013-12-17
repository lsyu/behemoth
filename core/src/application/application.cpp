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
#include "abstractevent.h"
#include "eventmouseclick.h"

#include "gl/freeglut.h"

#include "core/ogl/shader.h"
#include "core/ogl/vertexbufferobject.h"
#include "core/manager/resourcemanager.h"
#include "core/objects/2d/basic2dentity.h"

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
    : title("Unknown"), fullScreen(false), position(0,0), size(640,480), displaySize(0, 0),
      depth(EColorDepth::_32), painter(), windowId(0), secOfLastFrame(0)
{
}

void CApplication::initialize(int &argc, char *argv[])
{
    // Инициализация ресурсов.
    CResourceManager::getInstance()->initialize(argc, argv);

    // Инициализация glut
    glutInit(&argc, argv);
    displaySize = glm::ivec2(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
}

CApplication::~CApplication()
{
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

glm::ivec2 CApplication::getDisplaySize() const
{
    return displaySize;
}

void CApplication::setColorDepth(EColorDepth depth)
{
    this->depth = depth;
}

EColorDepth CApplication::getColorDepth() const
{
    return depth;
}

float CApplication::getSecondOfLastFrame() const
{
    return secOfLastFrame;
}

glm::vec2 CApplication::getRelativeCoordinate(const glm::ivec2 &absoluteCoordinate)
{
    float x = (absoluteCoordinate.x / instance->size.x - 0.5f) * 2.0f;
    float y = (absoluteCoordinate.y / instance->size.y - 0.5f) * 2.0f;
    return glm::vec2(x, y);
}

glm::vec2 CApplication::getRelativeCoordinate(int _x, int _y)
{
    float x = ((float)_x / (float)instance->size.x - 0.5f) * 2.0f;
    float y = ((float)_y / (float)instance->size.y - 0.5f) * 2.0f;
    return glm::vec2(x, y);
}


void CApplication::key(unsigned char key, int x, int y )
{
    if (key == 27 || key == 'q' || key == 'Q')
        glutLeaveMainLoop();
}

void CApplication::mouse(int button, int state, int x, int y)
{
    Basic2dEntity::objects4Event.clear();

    EMouseButton btn  = EMouseButton::left;
    if (button == GLUT_RIGHT_BUTTON)
        btn = EMouseButton::right;
    else if (button == GLUT_MIDDLE_BUTTON)
        btn = EMouseButton::middle;
    EMouseState s = (state == GLUT_UP ? EMouseState::up : EMouseState::down);

    CEventMouseClick e(x, y, btn, s);
    if (!instance->painter->updateGL(&e))
        glutLeaveMainLoop();
}

void CApplication::display()
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    instance->painter->paintGL();
    glutSwapBuffers();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<float> time_span = duration_cast< duration<double> >(t2 - t1);
    instance->secOfLastFrame = time_span.count();
//    std::cout << 1.0f / instance->secOfLastFrame << "\n";
}

void CApplication::idle()
{
    instance->painter->updateGL();
    glutPostRedisplay();
}

void CApplication::exec()
{
    if (painter && displaySize.x) {
        glutInitContextVersion(2, 1);
        glutInitWindowPosition(position.x, position.y);
        glutInitWindowSize(size.x, size.y);
        windowId = glutCreateWindow(title.c_str());
        glutKeyboardFunc(&CApplication::key);
        glutMouseFunc(&CApplication::mouse);
        glutDisplayFunc(&CApplication::display);
        glutIdleFunc(&CApplication::idle);
        instance->painter->prepareGL();

        glutMainLoop();
    }
}

void CApplication::close()
{
    glutLeaveMainLoop();
}

void CApplication::setScene(AbstractScene *painter)
{
    this->painter = painter;
}

} // namespace Core
