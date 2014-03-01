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
#include "core/factory/shaderfactory.h"
#include "core/manager/guimanager.h"
#include "core/objects/2d/basic2dentity.h"

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
    Basic2dEntity *object = CGUIManager::getInstance()->getRootObject();
    object->onClicked(*e);
    if (!Basic2dEntity::objects4Event.empty()) {
        bool clicked;
        do {
            clicked = CGUIManager::getInstance()->runOnClickFor(Basic2dEntity::objects4Event.back());
            Basic2dEntity::objects4Event.pop_back();
            if (Basic2dEntity::objects4Event.empty())
                break;
        } while (!clicked);
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
        CGUIManager::getInstance()->getRootObject()->paint();
        shader->disable();
    }

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}



} //namespace core
