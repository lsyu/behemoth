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

#ifndef BASICSCENE3DLAYER_H
#define BASICSCENE3DLAYER_H

#include "abstractlayer.h"
#include <vector>
#include <string>

namespace behemoth {

class CBasicNode;

/**
 * @brief Базовый класс слоя трехмерной сцены.
 */
class CBasicScene3dLayer : public AbstractLayer
{
public:
    explicit CBasicScene3dLayer(const std::string &fileName);
    virtual ~CBasicScene3dLayer();

    virtual void prepareGL() override;
    virtual bool updateGL() override;
    virtual void paintGL() override;

protected:
    CBasicNode* m_rootNode; /**< Главный узел сцены. */
    std::string m_fileName; /**< Название скрипта описания GUI */
}; // class CBasicScene3dLayer

} // namespace behemoth

#endif // BASICSCENE3DLAYER_H
