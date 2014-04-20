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

#ifndef BASICNODE_H
#define BASICNODE_H

#include "glm/glm.h"
#include "glm/gtx/quaternion.hpp"

#include <string>
#include <set>

namespace bhm {

class CBasic3dEntity;

/**
 * @brief Базовый класс вершины графа сцены.
 * Данная сущность необходима для определения положения сущности в пределах сцены.
 * @note Для того, чтобы отрисовать сущность, необходимо знание о ее положении в пространстве.
 * @todo Реализовать отсечение простанства.
 */
class CBasicNode
{
    friend class CNodeFactory;
public:
    using CChilds = std::set<CBasicNode*>;
    using CEntities3d = std::set<CBasic3dEntity*>;

    explicit CBasicNode(const std::string &id);
    ~CBasicNode();

    void setId(const std::string &id);
    std::string getId() const;

    void setPosition(const glm::vec3 &position);
    glm::vec3 getPosition() const;

    void setOrientation(float angle, const glm::vec3 &axis);
    glm::quat getOrientation() const;
    glm::vec3 getDirection() const;

    void rotate(float angle, const glm::vec3 &axis = {0.0f, 0.0f, 1.0f});
    void translate(const glm::vec3 &shift);

    glm::mat4 getModelMatrix() const;

    void addEntity3d(CBasic3dEntity *entity);
    void addEntity3d(const std::string &nameOfEntity);
    CEntities3d getEntities() const;
    CBasic3dEntity *getEntity(const std::string &nameOfEntity) const;
    std::string getNameOfFirstEntity() const;

    void addChild(CBasicNode *node);
    void addChild(const std::string &nameOfNode);
    CChilds getChilds() const;
    CBasicNode *getChild(const std::string &nameOfNode) const;

    void configureEntities();
    bool onUpdateEntities();
    void paintEntities();

    bool operator <(const CBasicNode &other) const;
private:

    std::string m_id;           /**< Название ребра. */
    glm::quat m_orientation;    /**< Ориентация. */
    glm::vec3 m_position;       /**< Позиция. */
    CEntities3d m_entities;     /**< Объекты, прикрепленные к данному узлу. */
    CChilds m_childs;           /**< Дочерние узлы данного узла. */
}; // class behemoth

} // class behemoth

#endif // BASICNODE_H
