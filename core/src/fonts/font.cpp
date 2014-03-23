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

int CFont::quantity = 50;

CFont::CFont(const std::string &name, int height) : name(name), height(height),
    vAlign(EVerticalAlign::Center), hAlign(EHorizontalAlign::Center), color(1, 0, 0)
{
}

CFont::~CFont()
{
}

void CFont::setName(const std::string &name)
{
    this->name = name;
}

std::string CFont::getName() const
{
    return name;
}

void CFont::setQuantity(int _quantity)
{
    quantity = _quantity;
}

int CFont::getQuantity()
{
    return quantity;
}

void CFont::setHeight(float height)
{
    this->height = height;
}

float CFont::getHeight() const
{
    return height;
}

void CFont::setVericalAlign(EVerticalAlign vAlign)
{
    this->vAlign = vAlign;
}

EVerticalAlign CFont::getVerticalAlign() const
{
    return vAlign;
}

void CFont::setHorizontalAlign(EHorizontalAlign hAlign)
{
    this->hAlign = hAlign;
}

EHorizontalAlign CFont::getHorizontalAlign() const
{
    return hAlign;
}

void CFont::setColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec3 CFont::getColor() const
{
    return color;
}

} // namespace behemoth
