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

#include "basic3dentity.h"

#include <algorithm>

#include "glm/ext.h"

#include "core/ogl/ogl.h"

namespace behemoth {

CBasic3dEntity::CBasic3dEntity(const std::string &id) : AbstractEntity(), m_id(id), m_childs(), m_parent(nullptr),
    m_vertices(), m_indexes(), m_vao(), m_vertexVBO(), m_indexVBO(EArrayType::Index)
{
}

CBasic3dEntity::~CBasic3dEntity()
{
    for(CBasic3dEntity *item: m_childs)
        delete item;
}

void CBasic3dEntity::configure()
{
    m_vao.genBuffer();
    m_vao.bind();
    m_vertexVBO.genBuffer();
    m_vertexVBO.setData(&m_vertices);
    m_indexVBO.genBuffer();
    m_indexVBO.setData(&m_indexes);
    m_vao.disable();

    for (CBasic3dEntity *obj: m_childs)
        obj->configure();
}

void CBasic3dEntity::paint() const
{

    // Индексы - unsigned short int по 3 на полигон
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, m_indexes.size() * 3, GL_UNSIGNED_SHORT, static_cast<void*>(0));
    m_vao.disable();

    for (CBasic3dEntity *obj: m_childs)
        obj->paint();
}

std::string CBasic3dEntity::getId() const
{
    return m_id;
}

void CBasic3dEntity::setParent(CBasic3dEntity *parent)
{
    m_parent = parent;
}

CBasic3dEntity *CBasic3dEntity::getParent() const
{
    return m_parent;
}

bool CBasic3dEntity::isRoot() const
{
    return m_parent == nullptr;
}

void CBasic3dEntity::addChild(CBasic3dEntity *child)
{
    m_childs.push_back(child);
}

CBasic3dEntity *CBasic3dEntity::getChild(const std::string &id)
{
    CChilds3D::const_iterator it = std::find_if(m_childs.begin(), m_childs.end(),
    [&id](CBasic3dEntity *child) -> bool
    {
        return child->getId() == id;
    });
    if (it != m_childs.end())
        return (CBasic3dEntity *)(&(*it));
    return nullptr;
}

std::vector<CBasic3dEntity *> &CBasic3dEntity::getChilds()
{
    return m_childs;
}

} // namespace behemoth
