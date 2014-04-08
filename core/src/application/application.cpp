/*
 * behemoth is graphics engine with lua-based declarative language for designing user interface and 3d stuff.
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
#include "abstractlayer.h"

#include "gl/freeglut.h"

#include "core/ogl/shader.h"
#include "core/ogl/vertexbufferobject.h"

#include "core/events/abstractevent.h"
#include "core/events/eventmouseclick.h"

#include "core/lua/resourcemanager.h"
#include "core/objects/gui/entity2dfactory.h"

#include <iostream>
#include <chrono>

namespace behemoth {

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
    : m_title("Unknown"), m_isFullScreen(false), m_position(0,0), m_size(640,480), m_displaySize(0, 0),
      m_depth(EColorDepth::_32), m_guiLayer(nullptr), m_windowId(0), m_secOfLastFrame(0)
{
}

void CApplication::initialize(int &argc, char *argv[])
{
    // Инициализация ресурсов.
    CResourceManager::getInstance()->initialize(argc, argv);

    // Инициализация glut
    glutInit(&argc, argv);
    m_displaySize = glm::ivec2(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
}

CApplication::~CApplication()
{
}

void CApplication::setWindowTitle(const std::string &title)
{
    this->m_title = title;
}

std::string CApplication::getWindowTitle() const
{
    return m_title;
}

void CApplication::setFullScreen(bool fullScreen)
{
    this->m_isFullScreen = fullScreen;
}

bool CApplication::isFullScreen() const
{
    return m_isFullScreen;
}

void CApplication::setPosition(const glm::ivec2 &position)
{
    this->m_position = position;
}

glm::ivec2 CApplication::getPosition() const
{
    return m_position;
}

void CApplication::setSize(const glm::ivec2 &size)
{
    this->m_size = size;
}

glm::ivec2 CApplication::getSize() const
{
    return m_size;
}

glm::ivec2 CApplication::getDisplaySize() const
{
    return m_displaySize;
}

void CApplication::setColorDepth(EColorDepth depth)
{
    this->m_depth = depth;
}

EColorDepth CApplication::getColorDepth() const
{
    return m_depth;
}

float CApplication::getSecondOfLastFrame() const
{
    return m_secOfLastFrame;
}

glm::vec2 CApplication::getRelativeCoordinate(const glm::ivec2 &absoluteCoordinate)
{
    float x = (absoluteCoordinate.x / instance->m_size.x - 0.5f) * 2.0f;
    float y = (absoluteCoordinate.y / instance->m_size.y - 0.5f) * 2.0f;
    return glm::vec2(x, y);
}

glm::vec2 CApplication::getRelativeCoordinate(int _x, int _y)
{
    float x = ((float)_x / (float)instance->m_size.x - 0.5f) * 2.0f;
    float y = ((float)_y / (float)instance->m_size.y - 0.5f) * 2.0f;
    return glm::vec2(x, y);
}

float CApplication::getAspectRatio() const
{
    return m_size.y != 0 ? static_cast<float>(m_size.x) / static_cast<float>(m_size.y) : 1.0f;
}


void CApplication::key(unsigned char key, int x, int y )
{
    if (key == 27 || key == 'q' || key == 'Q')
        glutLeaveMainLoop();
}

void CApplication::mouse(int button, int state, int x, int y)
{
    CEntity2dFactory::getInstance()->getEntities4Event().clear();

    EMouseButton btn  = EMouseButton::left;
    if (button == GLUT_RIGHT_BUTTON)
        btn = EMouseButton::right;
    else if (button == GLUT_MIDDLE_BUTTON)
        btn = EMouseButton::middle;
    EMouseState s = (state == GLUT_UP ? EMouseState::up : EMouseState::down);

    CEventMouseClick e(x, y, btn, s);
    if (instance->m_guiLayer && !instance->m_guiLayer->updateGL(&e))
        glutLeaveMainLoop();
    else if (instance->m_sceneLayer && !instance->m_sceneLayer->updateGL(&e))
        glutLeaveMainLoop();
}

void CApplication::display()
{
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    if (instance->m_sceneLayer)
        instance->m_sceneLayer->paintGL();
    if (instance->m_guiLayer)
        instance->m_guiLayer->paintGL();
    glutSwapBuffers();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<float> time_span = duration_cast< duration<double> >(t2 - t1);
    instance->m_secOfLastFrame = time_span.count();
//    std::cout << 1.0f / instance->m_secOfLastFrame << "\n";
}

void CApplication::idle()
{
    if (instance->m_guiLayer)
        instance->m_guiLayer->updateGL();
    if (instance->m_sceneLayer)
        instance->m_sceneLayer->updateGL();
    glutPostRedisplay();
}

void CApplication::exec()
{
    if (m_guiLayer && m_displaySize.x) {
        glutInitContextVersion(2, 1);
        glutInitWindowPosition(m_position.x, m_position.y);
        glutInitWindowSize(m_size.x, m_size.y);
        m_windowId = glutCreateWindow(m_title.c_str());
        glutKeyboardFunc(&CApplication::key);
        glutMouseFunc(&CApplication::mouse);
        glutDisplayFunc(&CApplication::display);
        glutIdleFunc(&CApplication::idle);
        if (instance->m_guiLayer)
            instance->m_guiLayer->prepareGL();
        if (instance->m_sceneLayer)
            instance->m_sceneLayer->prepareGL();

        glutMainLoop();
    }
}

void CApplication::close()
{
    glutLeaveMainLoop();
}

void CApplication::setGUILayer(AbstractLayer *guiLayer)
{
    if (m_guiLayer && m_guiLayer != guiLayer)
        delete m_guiLayer;
    m_guiLayer = guiLayer;
}

void CApplication::setScene3DLayer(AbstractLayer *scene3D)
{
    if (m_sceneLayer && m_sceneLayer != scene3D)
        delete m_sceneLayer;
    m_sceneLayer = scene3D;
}

} // namespace behemoth
