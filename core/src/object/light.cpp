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

#include "light.h"
#include "glm/ext.h"

namespace Core {

void Light::initLight(const glm::vec3 &position,
                      const glm::vec3 &center,
                      const glm::vec3 &up,
                      float left, float right,
                      float bottom, float top,
                      float near, float far)
{
    camLight.initCameraOrtho(left, right, bottom, top, near, far);
    this->position = position;
    this->direction = glm::normalize<float>(center - position);
    this->up = up;
    camLight.lookAt(position, position + direction, up);
}

void Light::setPosition(const glm::vec3 &position)
{
    camLight.setPosition(position);
    this->position = camLight.getPosition();
    this->direction = camLight.getDirection();
}

void Light::setPosition(float x, float y, float z)
{
    setPosition(glm::vec3(x, y, z));
}

glm::vec3 Light::getPosition() const
{
    return position;
}

void Light::setDirection(const glm::vec3 &direction)
{
    camLight.lookAt(position, direction, up);
    this->direction = glm::normalize<float>(direction);
}

void Light::setDirection(float x, float y, float z)
{
    setPosition(glm::vec3(x, y, z));
}

glm::vec3 Light::getDirection() const
{
    return direction;
}

void Light::rotateView(float angle, float x, float y, float z)
{
    camLight.rotateView(angle, x, y, z);
    this->direction = camLight.getDirection();
}

void Light::rotateViewUpBottom(float angle)
{
    camLight.rotateViewUpBottom(angle);
    this->direction = camLight.getDirection();
}

void Light::rotatePosition(float angle, float x, float y, float z)
{
    camLight.rotatePosition(angle, x, y, z);
    this->position = camLight.getPosition();
    this->direction = camLight.getDirection();
}

void Light::rotatePositionUpBottom(float angle)
{
    camLight.rotatePositionUpBottom(angle);
    this->position = camLight.getPosition();
    this->direction = camLight.getDirection();
}

void Light::translate(const glm::vec3 &shift)
{
    camLight.translate(shift);
    this->position = camLight.getPosition();
    this->direction = camLight.getDirection();
}

void Light::translate(float x, float y, float z)
{
    translate(glm::vec3(x, y, z));
}

Camera Light::getCameraOfLight() const
{
    return camLight;
}

} // namespace Core

