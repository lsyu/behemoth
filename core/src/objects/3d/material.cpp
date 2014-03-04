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

#include "material.h"

namespace Core {

Material::Material(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular)
    : ambient(ambient),
      diffuse(diffuse),
      specular(specular),
      shading(Phong)
{
}

Material::Material(float roughness, float refraction)
    : roughness(roughness),
      refraction(refraction),
      shading(CoockTorrance)
{
}

void Material::setAmbient(const glm::vec4 &ambient)
{
    this->ambient = ambient;
    setShading(Material::Phong);
}

void Material::setAmbient(float r, float g, float b, float a)
{
    setAmbient(glm::vec4(r, g, b, a));
}

glm::vec4 Material::getAmbient() const
{
    return ambient;
}

void Material::setDiffuse(const glm::vec4 &diffuse)
{
    this->diffuse = diffuse;
    setShading(Material::Phong);
}

void Material::setDiffuse(float r, float g, float b, float a)
{
    setDiffuse(glm::vec4(r, g, b, a));
}

glm::vec4 Material::getDiffuse() const
{
    return diffuse;
}

void Material::setSpecular(const glm::vec4 &specular)
{
    this->specular = specular;
    setShading(Material::Phong);
}

void Material::setSpecular(float r, float g, float b, float a)
{
    setSpecular(glm::vec4(r, g, b, a));
}

glm::vec4 Material::getSpecular() const
{
    return specular;
}

void Material::setRoughness(float roughness)
{
    this->roughness = roughness;
    setShading(Material::CoockTorrance);
}

float Material::getRoughness() const
{
    return roughness;
}

void Material::setRefraction(float refraction)
{
    this->refraction = refraction;
    setShading(Material::CoockTorrance);
}

float Material::getRefraction() const
{
    return refraction;
}

Material::Shading Material::getShading() const
{
    return this->shading;
}

void Material::setShading(Shading shading)
{
    this->shading = shading;
}

} // namespace Core
