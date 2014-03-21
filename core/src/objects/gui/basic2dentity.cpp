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

#include "basic2dentity.h"

#include <algorithm>

namespace core {

std::vector<CBasic2dEntity*> CBasic2dEntity::objects4Event;

CBasic2dEntity::CBasic2dEntity() : id(), vPos2(), vUV(), vColor(), vChilds(), parent(nullptr)
{
}

CBasic2dEntity::CBasic2dEntity(const std::string &id) : AbstractEntity(), id(id), vPos2(), vUV(),
    vColor(), vChilds(), parent(nullptr)
{
}

CBasic2dEntity::~CBasic2dEntity()
{
}

std::string CBasic2dEntity::getId() const
{
    return id;
}

void CBasic2dEntity::setId(const std::string &id)
{
    this->id = id;
}

void CBasic2dEntity::setParent(CBasic2dEntity *parent)
{
    this->parent = parent;
    if (!parent->getChild(this->id))
        parent->addChild(this);
}

CBasic2dEntity *CBasic2dEntity::getParent() const
{
    return parent;
}

bool CBasic2dEntity::isRoot() const
{
    return parent == nullptr;
}

void CBasic2dEntity::addChild(CBasic2dEntity *child)
{
    vChilds.push_back(child);
    child->setParent(this);
}

CBasic2dEntity *CBasic2dEntity::getChild(const std::string &id)
{
    std::vector<CBasic2dEntity *>::const_iterator it = std::find_if(vChilds.begin(), vChilds.end(),
    [&id](CBasic2dEntity *child) -> bool
    {
        return child->getId() == id;
    });
    if (it != vChilds.end())
        return (CBasic2dEntity *)(&(*it));
    return nullptr;
}

std::vector<CBasic2dEntity *> &CBasic2dEntity::getChilds()
{
    return vChilds;
}

} // namespace core
