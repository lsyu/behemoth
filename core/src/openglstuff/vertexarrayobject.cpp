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

#include "vertexarrayobject.h"

#include "allegro5/allegro5.h"
#include "allegro5/allegro_opengl.h"

VertexArrayObject::VertexArrayObject() : vao(0)
{
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &vao);
}

void VertexArrayObject::genBuffer()
{
    glGenVertexArrays(1, &vao);
}

void VertexArrayObject::bind() const
{
    glBindVertexArray(vao);
}

void VertexArrayObject::disable() const
{
    glBindVertexArray(0);
}
