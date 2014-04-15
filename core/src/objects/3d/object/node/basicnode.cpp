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

#include "basicnode.h"
#include "glm/ext.h"

namespace behemoth {

CBasicNode::CBasicNode(const std::string &name) : m_name(name), m_orientation(), m_position()
{
}

CBasicNode::~CBasicNode()
{
//    for(CBasicNode *node: m_childs)
//        delete node;
}

std::string CBasicNode::getName() const
{
    return m_name;
}

void CBasicNode::setPosition(const glm::vec3 &position)
{
    m_position = position;
}

glm::vec3 CBasicNode::getPosition() const
{
    return m_position;
}

void CBasicNode::rotate(float angle, const glm::vec3 &axis)
{

    m_orientation *= glm::angleAxis(angle, axis);
}

void CBasicNode::translate(const glm::vec3 &shift)
{
    m_position += shift;
}

glm::mat4 CBasicNode::getModelMatrix() const
{
    return glm::translate(glm::mat4(), m_position) * glm::toMat4(m_orientation);
}

//CBasicNode::CChilds CBasicNode::getChilds() const
//{
//    return m_childs;
//}

} // namespace behemoth
