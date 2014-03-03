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

#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <vector>
#include "glm/glm.h"

/**
 * @brief Адаптер для работы с VBO.
 *
 * Подробно о VBO смотри на opengl.org
 */
class CVertexBufferObject
{
public:
    /**
     * @brief Конструктор по-умолчанию.
     *
     * Перед началом работы с VBO, его нужно сгенерировать!
     * @sa genBuffer
     */
    CVertexBufferObject();
    virtual ~CVertexBufferObject();
    /**
     * @brief Генерирование VBO.
     */
    void genBuffer();
    /**
     * @brief Сделать VBO активным.
     */
    void bind() const;
    /**
     * @brief Сделать VBO неактивным.
     **/
    void disable() const;

    /**
     * @brief Заполнить VBO данными.
     */
    void setData(const std::vector<glm::vec2> *buffer) const;
    /**
     * @brief Заполнить VBO данными.
     */
    void setData(const std::vector<glm::vec3> *buffer) const;
    /**
     * @brief Заполнить VBO данными.
     */
    void setData(const std::vector<glm::vec4> *buffer) const;

private:
    uint vbo;

}; // class VertexBufferObject

#endif // VERTEXBUFFEROBJECT_H
