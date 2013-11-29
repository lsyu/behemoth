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
#include "event.h"

#include "gl/freeglut.h"

#include "core/ogl/shader.h"
#include "core/ogl/vertexbufferobject.h"
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

void CApplication::key(unsigned char key, int x, int y )
{
    if (key == 27 || key == 'q' || key == 'Q')
        glutLeaveMainLoop();
    else {
        CEvent e;
        instance->updateGL(&e);
    }

}

void CApplication::display()
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    instance->paintGL();
    glutSwapBuffers();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<float> time_span = duration_cast< duration<double> >(t2 - t1);
    instance->secOfLastFrame = time_span.count();
    std::cout << 1.0f / instance->secOfLastFrame << "\n";
}

void CApplication::idle()
{
    CEvent e;
    instance->updateGL(&e);
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
        glutDisplayFunc(&CApplication::display);
        glutIdleFunc(&CApplication::idle);
        prepareGL();

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

void CApplication::prepareGL()
{
    painter->prepareGL();
}

void CApplication::updateGL(CEvent *e)
{
    if (!painter->updateGL(e))
        glutLeaveMainLoop();
}

void CApplication::paintGL()
{
    painter->paintGL();
}

} // namespace Core
