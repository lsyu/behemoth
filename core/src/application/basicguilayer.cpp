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

#include "basicguilayer.h"

#include "core/ogl/ogl.h"
#include "core/ogl/shaderfactory.h"
#include "core/lua/guimanager.h"
#include "core/objects/gui/entity2dfactory.h"
#include "core/events/eventmouseclick.h"

namespace behemoth {


CBasicGUILayer::CBasicGUILayer(const std::string &fileName) : AbstractLayer(),
    m_root(nullptr), m_fileName(fileName)
{
}

CBasicGUILayer::~CBasicGUILayer()
{
}

void CBasicGUILayer::prepareGL()
{
    // m_root инициализируется здесь, потому что только к этому моменту можно сказать,
    // что контекст OpenGl создан.
    m_root = CEntity2dFactory::getInstance()->loadGUI(m_fileName);
    if (m_root)
        m_root->configure();
}

bool CBasicGUILayer::updateGL()
{
    return true;
}

bool CBasicGUILayer::updateGL(CEventMouseClick *e)
{
    if (m_root) {
        static CBasic2dEntity *entityDown = nullptr, *entityUp = nullptr;
        EMouseState state = e->getMouseState();
        m_root->onClicked(*e);
        if (!CEntity2dFactory::getInstance()->getEntities4Event().empty()) {
            if (state == EMouseState::down) {
                entityDown = CEntity2dFactory::getInstance()->getEntities4Event().back();
                entityUp = nullptr;
                executeAction(&CGUIManager::onPressed);
            } else {
                entityUp = CEntity2dFactory::getInstance()->getEntities4Event().back();
                executeAction(&CGUIManager::onReleased);
            }
            if (entityUp && entityDown && entityDown->getId() == entityUp->getId()) {
                entityUp = entityDown = nullptr;
                executeAction(&CGUIManager::onClick);
            }
        }
    }
    return true;
}

void CBasicGUILayer::paintGL()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_root)
        m_root->paint();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void CBasicGUILayer::executeAction(bool (CGUIManager::*action)(AbstractEntity *))
{
    std::vector<CBasic2dEntity*> tmp = CEntity2dFactory::getInstance()->getEntities4Event();
    while (true) {
        if ((CGUIManager::getInstance()->*action)(CEntity2dFactory::getInstance()->getEntities4Event().back()))
            break;
        CEntity2dFactory::getInstance()->getEntities4Event().pop_back();
        if (CEntity2dFactory::getInstance()->getEntities4Event().empty())
            break;
    }
    CEntity2dFactory::getInstance()->getEntities4Event() = tmp;
}



} //namespace behemoth
