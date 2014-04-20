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

#include "basiclight.h"

namespace bhm {

CBasicLight::CBasicLight() : AbstractLight(), m_ambient(0.0f, 0.0f, 0.0f),
    m_diffuse(1.0f, 1.0f, 1.0f), m_specular(1.0f, 1.0f, 1.0f)
{
}

CBasicLight::~CBasicLight()
{
}

void CBasicLight::setAmbient(const glm::vec3 &ambient)
{
    this->m_ambient = ambient;
}

void CBasicLight::setAmbient(float r, float g, float b)
{
    setAmbient(glm::vec3(r, g, b));
}

glm::vec3 CBasicLight::getAmbient() const
{
    return m_ambient;
}

void CBasicLight::setDiffuse(const glm::vec3 &diffuse)
{

    this->m_diffuse = diffuse;
}

void CBasicLight::setDiffuse(float r, float g, float b)
{
    setDiffuse(glm::vec3(r, g, b));
}

glm::vec3 CBasicLight::getDiffuse() const
{
    return m_diffuse;
}

void CBasicLight::setSpecular(const glm::vec3 &specular)
{
    this->m_specular = specular;
}

void CBasicLight::setSpecular(float r, float g, float b)
{
    setSpecular(glm::vec3(r, g, b));
}

glm::vec3 CBasicLight::getSpecular() const
{
    return m_specular;
}

} // namespace behemoth
