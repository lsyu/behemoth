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

#include "gl/gl.h"
#include "gl/glext.h"

namespace core {

CVertexBufferObject::CVertexBufferObject(EArrayType type) : mVBO(0), mType(type)
{
}

CVertexBufferObject::~CVertexBufferObject()
{
    if (mVBO >= 0)
        glDeleteBuffers(1, &mVBO);
}

void CVertexBufferObject::genBuffer()
{
    glGenBuffers(1, &mVBO);
}

void CVertexBufferObject::bind() const
{
    glBindBuffer(mType == EArrayType::Data ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, mVBO);
}

void CVertexBufferObject::disable() const
{
    glBindBuffer(mType == EArrayType::Data ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CVertexBufferObject::setData(const void *data, size_t sizeOfData) const
{
    bind();
    glBufferData(mType == EArrayType::Data ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER,
                 sizeOfData, data, GL_STATIC_DRAW);
}

} // namespace core
