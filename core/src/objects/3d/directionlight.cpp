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

#include "directionlight.h"

namespace behemoth {

CDirectionLight::CDirectionLight() : CPointLight(), mDirection(0.0f, 0.0f, -1.0f)
{
}

CDirectionLight::~CDirectionLight()
{
}

void CDirectionLight::setDirection(const glm::vec3 &direction)
{
    this->mDirection = direction;
}

void CDirectionLight::setDirection(float x, float y, float z)
{
    setDirection(glm::vec3(x, y, z));
}

glm::vec3 CDirectionLight::getDirection() const
{
    return mDirection;
}

} // namespace behemoth
