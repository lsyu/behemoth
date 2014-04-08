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
#include <string>
#include <vector>

namespace behemoth {

/**
 * @brief Базовый класс вершины графа сцены.
 * Данная сущность необходима для определения положения сущности в пределах сцены.
 * @todo Реализовать отсечение простанства.
 * @todo Реализовать вращение при помощи кватернионов.
 * @todo перемещение/вращение детей.
 */
class CBasicNode
{
    friend class CNodeFactory;
public:
    using CChilds = std::vector<CBasicNode*>;

    explicit CBasicNode(const std::string &name);
    ~CBasicNode();

    /**
     * @brief Получить имя.
     */
    std::string getName() const;
    /**
     * @brief Установить позицию узла.
     */
    void setPosition(const glm::vec3 &position);
    const glm::vec3 &getPosition() const;
    /**
     * @brief вращение узла.
     */
    void rotate(float angle, const glm::vec3 &axis = {0.0f, 0.0f, 1.0f});
    /**
     * @brief Перемещение узла.
     * @param shift вектор смещения.
     */
    void translate(const glm::vec3 &shift);
    /**
     * @brief Получить модельную матрицу.
     */
    glm::mat4 getModelMatrix() const;
    /**
     * @brief Получить детей.
     */
    CChilds getChilds() const;
private:

    std::string m_name;             /**< Название ребра. */
    glm::mat4 m_modelMatrix;        /**< Модельная матрица. */
    CChilds m_childs;               /**< Дети данной вершины. */
}; // class behemoth

} // class behemoth

#endif // BASICNODE_H
