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

#ifndef BASICGUILAYER_H
#define BASICGUILAYER_H

#include "abstractlayer.h"

namespace core {

class CShader;
class CGUIManager;
class CBasic2dEntity;

/**
 * @brief Базовый класс слоя пользовательского интерфейса.
 *
 * Для того, чтобы создать пользовательский слой GUI, необходимо
 * наследоваться от данного класса и определить реализацию метода
 * virtual void prepareGL() из интерфейса AbstractLayer.
 * Для формирования данных для отрисовки пользовательского интерфейса
 * достаточно выполнить CGUIManager::getInstance()->readGui("example.lua");
 */
class CBasicGUILayer : public AbstractLayer
{
public:
    CBasicGUILayer();
    virtual ~CBasicGUILayer();

    virtual bool updateGL() override;
    virtual bool updateGL(CEventMouseClick *e) override;
    virtual void paintGL() override;

private:
    /**
     * @brief Выполнить действие action
     */
    void executeAction(bool(CGUIManager::*action)(CBasic2dEntity *));
}; // class CBasicGUILayer

} // namespace core

#endif // BASICGUILAYER_H
