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

CVertexArrayObject::CVertexArrayObject() : vao(0)
{
}

CVertexArrayObject::~CVertexArrayObject()
{
    glDeleteVertexArrays(1, &vao);
}

void CVertexArrayObject::genBuffer()
{
    glGenVertexArrays(1, &vao);
}

void CVertexArrayObject::bind() const
{
    glBindVertexArray(vao);
}

void CVertexArrayObject::disable() const
{
    glBindVertexArray(0);
}
