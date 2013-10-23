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

#include "vertexbufferobject.h"

#include "allegro5/allegro5.h"
#include "allegro5/allegro_opengl.h"

CVertexBufferObject::CVertexBufferObject() : vbo(0)
{
}

CVertexBufferObject::~CVertexBufferObject()
{
    if (vbo >= 0)
        glDeleteBuffers(1, &vbo);
}

void CVertexBufferObject::genBuffer()
{
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
}

void CVertexBufferObject::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void CVertexBufferObject::disable() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CVertexBufferObject::setData(const std::vector<glm::vec2> *buffer) const
{
    bind();
    //! TODO: Подумать насчет STATIC_DRAW!
    glBufferData(GL_ARRAY_BUFFER, buffer->size() * sizeof(glm::vec2), &(*buffer)[0], GL_STATIC_DRAW);
}

void CVertexBufferObject::setData(const std::vector<glm::vec3> *buffer) const
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, buffer->size() * sizeof(glm::vec3), &(*buffer)[0], GL_STATIC_DRAW);
}

void CVertexBufferObject::setData(const std::vector<glm::vec4> *buffer) const
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, buffer->size() * sizeof(glm::vec4), &(*buffer)[0], GL_STATIC_DRAW);
}
