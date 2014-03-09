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

#include "basicguilayer.h"

#include "core/ogl/ogl.h"
#include "core/ogl/shaderfactory.h"
#include "core/lua/guimanager.h"
#include "core/objects/gui/basic2dentity.h"

#include "core/events/eventmouseclick.h"

namespace core {


CBasicGUILayer::CBasicGUILayer() : AbstractLayer(), shader(nullptr)
{
}

CBasicGUILayer::~CBasicGUILayer()
{
}

bool CBasicGUILayer::updateGL()
{
    return true;
}

bool CBasicGUILayer::updateGL(CEventMouseClick *e)
{
    static CBasic2dEntity *entityDown = nullptr, *entityUp = nullptr;
    EMouseState state = e->getMouseState();
    CBasic2dEntity *object = CGUIManager::getInstance()->getRootObject();
    object->onClicked(*e);
    if (!CBasic2dEntity::objects4Event.empty()) {
        if (state == EMouseState::down) {
            entityDown = CBasic2dEntity::objects4Event.back();
            entityUp = nullptr;
            executeAction(&CGUIManager::onPressed);
        } else {
            entityUp = CBasic2dEntity::objects4Event.back();
            executeAction(&CGUIManager::onReleased);
        }
        if (entityUp && entityDown && entityDown->getId() == entityUp->getId()) {
            entityUp = entityDown = nullptr;
            executeAction(&CGUIManager::onClick);
        }
    }
    return true;
}

void CBasicGUILayer::paintGL()
{
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!shader) {
        shader = CShaderFactory::getInstance()->getShader("gui");
    } else {
        shader->bind();
        CBasic2dEntity *root = CGUIManager::getInstance()->getRootObject();
        if (root)
            root->paint();
        shader->disable();
    }

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void CBasicGUILayer::executeAction(bool (CGUIManager::*action)(AbstractEntity *))
{
    std::vector<CBasic2dEntity*> tmp = CBasic2dEntity::objects4Event;
    while (true) {
        if ((CGUIManager::getInstance()->*action)(CBasic2dEntity::objects4Event.back()))
            break;
        CBasic2dEntity::objects4Event.pop_back();
        if (CBasic2dEntity::objects4Event.empty())
            break;
    }
    CBasic2dEntity::objects4Event = tmp;
}



} //namespace core
