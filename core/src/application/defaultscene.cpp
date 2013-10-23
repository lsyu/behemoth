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

#include "defaultscene.h"

#include <vector>

#include "allegro5/allegro5.h"
#include "allegro5/allegro_opengl.h"

#include "core/manager/luamanager.h"
#include "core/factory/shaderfactory.h"
#include "core/objects/abstractentity.h"

namespace core {

DefaultScene::DefaultScene() : AbstractScene()
{
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::prepareGL()
{
    // TODO: путь из ресурсов
    CLuaManager::getInstance()->readGui("scripts/test.lua");

    //glShadeModel(GL_SMOOTH);    // ???
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);
}

bool DefaultScene::updateGL(ALLEGRO_EVENT *e)
{
    if (!e)
        return true;
    if (e->type == ALLEGRO_EVENT_KEY_DOWN)
        if (e->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            return false;
    return true;
}

void DefaultScene::paintGL()
{
    // TODO: После рисования 3d сцены чистить не нужно!
    //glEnable(GL_MULTISAMPLE);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader *shader = CShaderFactory::getInstance()->getShader("test");
    if (shader) {
        shader->bind();
        const std::vector<std::shared_ptr<AbstractEntity> > &objects = CLuaManager::getInstance()->getObjects();
        for (int i = objects.size()-1; i >= 0; --i)
            if (objects[i]->isRoot())
                objects[i]->paint();
        shader->disable();
    }

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_MULTISAMPLE);
}

} // namespace Core
