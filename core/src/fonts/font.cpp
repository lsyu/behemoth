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

#include "font.h"

namespace behemoth {

int CFont::m_quantity = 50;

CFont::CFont(const std::string &name, int height) : m_name(name), m_height(height), m_color(1, 0, 0)
{
}

CFont::~CFont()
{
}

void CFont::setName(const std::string &name)
{
    this->m_name = name;
}

std::string CFont::getName() const
{
    return m_name;
}

void CFont::setQuantity(int quantity)
{
    m_quantity = quantity;
}

int CFont::getQuantity()
{
    return m_quantity;
}

void CFont::setHeight(float height)
{
    this->m_height = height;
}

float CFont::getHeight() const
{
    return m_height;
}

void CFont::setColor(const glm::vec3 &color)
{
    this->m_color = color;
}

glm::vec3 CFont::getColor() const
{
    return m_color;
}

} // namespace behemoth
