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
#include "algorithm"

namespace core {

Basic2dEntity::Basic2dEntity() : id(), vPos2(), vUV(), vColor(), vChilds(), parent(nullptr)
{
}

Basic2dEntity::Basic2dEntity(const std::string &id) : AbstractEntity(id), id(id), vPos2(), vUV(),
    vColor(), vChilds(), parent(nullptr)
{
}

Basic2dEntity::~Basic2dEntity()
{
}

std::string Basic2dEntity::getId() const
{
    return id;
}

void Basic2dEntity::setParent(AbstractEntity *parent)
{
    this->parent = parent;
    if (!parent->getChild(this->id))
        parent->addChild(this);
}

AbstractEntity *Basic2dEntity::getParent() const
{
    return parent;
}

bool Basic2dEntity::isRoot() const
{
    return parent == nullptr;
}

void Basic2dEntity::addChild(AbstractEntity *child)
{
    vChilds.push_back(child);
    child->setParent(this);
}

AbstractEntity *Basic2dEntity::getChild(const std::string &id)
{
    std::vector<AbstractEntity *>::const_iterator it = std::find_if(vChilds.begin(), vChilds.end(),
    [&id](AbstractEntity *child) -> bool
    {
        return child->getId() == id;
    });
    if (it != vChilds.end())
        return (AbstractEntity *)(&(*it));
    return nullptr;
}

const std::vector<AbstractEntity *> &Basic2dEntity::getChilds() const
{
    return vChilds;
}

} // namespace core
