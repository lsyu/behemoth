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

#include "entity.h"
#include "core/manager/resourcemanager.h"

#include <fstream>
#include <algorithm>

namespace Core {

using namespace std;

Entity::Entity() : vPos2(), vPos3(), vNormal(), vUV(), vColor(), vChilds(), parent(nullptr),
        id(), root(true)
{
}

Entity::Entity(const string &id) : vPos2(), vPos3(), vNormal(), vUV(), vColor(), vChilds(),
    parent(nullptr), id(id), root(true)
{
}

Entity::~Entity()
{
    vChilds.clear();
}

std::string Entity::getId() const
{
    return id;
}

void Entity::setParent(Entity *parent)
{
    parent->addChild(this);
    this->parent = parent;
}

const Entity* Entity::getParent() const
{
    return parent;
}

Entity* Entity::getParent()
{
    return parent;
}

bool Entity::isRoot() const
{
    return root;
}

void Entity::addChild(Entity *child)
{
    child->parent = this;
    child->root = false;
    vChilds.push_back(child);
}

const Entity *Entity::getChild(const string &id) const
{
    std::vector<Entity*>::const_iterator it = std::find_if(vChilds.begin(), vChilds.end(),
            [&id](Entity* child) -> bool
            {
                return child->getId() == id;
            });
    if (it != vChilds.end())
        return (const Entity*)(&(*it));
    return nullptr;
}

Entity *Entity::getChild(const string &id)
{
    std::vector<Entity*>::const_iterator it = std::find_if(vChilds.begin(), vChilds.end(),
            [&id](Entity* child) -> bool
            {
                return child->getId() == id;
            });
    if (it != vChilds.end())
        return (Entity*)(&(*it));
    return nullptr;
}

const std::vector<Entity*>& Entity::getChilds() const
{
    return vChilds;
}

//bool Entity::loadData(const string &fileName)
//{
//    ifstream in(fileName);
//    if (!in.is_open())
//        return false;

//    char tmp;
//    glm::vec3 pos;
//    glm::vec3 norm;
//    glm::vec2 tex;

//    while (in.good()) {
//        in >> tmp;
//        switch(tmp)
//        {
//        case 'v':
//            in >> pos.x >> pos.y >> pos.z >> tmp;
//            vPos3.push_back(pos);
//            break;

//        case 'n':
//            in >> norm.x >> norm.y >> norm.z >> tmp;
//            vNormal.push_back(norm);
//            break;

//        case 't':
//            in >> tex.x >> tex.y >> tmp;
//            vUV.push_back(tex);
//            break;
//        }
//    }
//    in.close();
//    return true;
//}

} // namespace Core
