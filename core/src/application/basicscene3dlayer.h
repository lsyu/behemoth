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

#ifndef BASICSCENE3DLAYER_H
#define BASICSCENE3DLAYER_H

#include "abstractlayer.h"

namespace core {

/**
 * @brief Базовый класс слоя трехмерной сцены.
 *
 * Для того, чтобы создать пользовательский слой 3D, необходимо
 * наследоваться от данного класса и определить реализацию метода
 * virtual void prepareGL() из интерфейса AbstractLayer.
 */
class CBasicScene3dLayer : public AbstractLayer
{
public:
    CBasicScene3dLayer();
    virtual ~CBasicScene3dLayer();

    virtual void prepareGL() override;
    virtual bool updateGL() override;
    virtual void paintGL() override;
}; // class CBasicScene3dLayer

} // namespace core

#endif // BASICSCENE3DLAYER_H
