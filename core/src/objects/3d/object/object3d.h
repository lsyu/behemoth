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

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "entity/basic3dentity.h"
#include "node/basicnode.h"

#include "glm/glm.h"

#include <string>

namespace behemoth {

/**
 * @brief Объект сцены.
 */
class CObject3d
{
public:
    CObject3d(const std::string &name);
    ~CObject3d();

    void setPosition(const glm::vec3 &position);
    glm::vec3 getPosition() const;

    void setEntity(const std::string &entity);
    std::string getEntity() const;

    void configure();
    void paint();

private:
    CBasic3dEntity *m_entity; /**< Отображаемая сущность. */
    CBasicNode *m_node;       /**< Узел графа сцены. */
}; // class CObject3d

} // namespace behemoth

#endif // OBJECT3D_H
