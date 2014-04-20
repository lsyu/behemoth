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

#include "basic2dentity.h"

#include <algorithm>

namespace bhm {

CBasic2dEntity::CBasic2dEntity() : CBasic2dEntity("")
{
}

CBasic2dEntity::CBasic2dEntity(const std::string &id) : AbstractEntity(), m_id(id), m_childs(),
    m_parent(nullptr), m_vertices(), m_vao(), m_vertexVBO()
{
}

CBasic2dEntity::~CBasic2dEntity()
{
}

void CBasic2dEntity::paint() const
{
}

std::string CBasic2dEntity::getId() const
{
    return m_id;
}

void CBasic2dEntity::configure()
{
}

void CBasic2dEntity::setId(const std::string &id)
{
    this->m_id = id;
}

void CBasic2dEntity::setParent(CBasic2dEntity *parent)
{
    this->m_parent = parent;
    if (!parent->getChild(this->m_id))
        parent->addChild(this);
}

CBasic2dEntity *CBasic2dEntity::getParent() const
{
    return m_parent;
}

bool CBasic2dEntity::isRoot() const
{
    return m_parent == nullptr;
}

void CBasic2dEntity::addChild(CBasic2dEntity *child)
{
    m_childs.push_back(child);
    child->setParent(this);
}

CBasic2dEntity *CBasic2dEntity::getChild(const std::string &id)
{
    std::vector<CBasic2dEntity *>::const_iterator it = std::find_if(m_childs.begin(), m_childs.end(),
    [&id](CBasic2dEntity *child) -> bool
    {
        return child->getId() == id;
    });
    if (it != m_childs.end())
        return (CBasic2dEntity *)(&(*it));
    return nullptr;
}

std::vector<CBasic2dEntity *> &CBasic2dEntity::getChilds()
{
    return m_childs;
}

} // namespace behemoth
