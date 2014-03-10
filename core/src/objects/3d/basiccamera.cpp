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

#include "basiccamera.h"

#include "glm/gtc/constants.hpp"
#include "glm/ext.hpp"

namespace core {

CBasicCamera::CBasicCamera() : AbstractCamera(), eye(0.0f, 0.0f, 1.0f), center(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f), viewMatrix(), projectionMatrix()
{
}

void CBasicCamera::lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
    viewMatrix = glm::lookAt(eye, center, up);
}

void CBasicCamera::setEye(const glm::vec3 &eye)
{
    this->eye = eye;
    lookAt(eye, center, up);
}

void CBasicCamera::setEye(float x, float y, float z)
{
    setEye(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getEye() const
{
    return eye;
}

void CBasicCamera::setCenter(const glm::vec3 &center)
{
    this->center = center;
    lookAt(eye, center, up);
}

void CBasicCamera::setCenter(float x, float y, float z)
{
    setCenter(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getCenter() const
{
    return center;
}

void CBasicCamera::setUp(const glm::vec3 &up)
{
    this->up = up;
    lookAt(eye, center, up);
}

void CBasicCamera::setUp(float x, float y, float z)
{
    setUp(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getUp() const
{
    return up;
}

void CBasicCamera::rotateView(float angle, float x, float y, float z)
{
    if (x == 0 && y == 0 && z == 0) {
        x = up.x;
        y = up.y;
        z = up.z;
    }
    center -= eye;
    glm::vec3 view = center;

    float SinA = glm::sin<float>(glm::pi<float>() * angle / 180.0f);
    float CosA = glm::cos<float>(glm::pi<float>() * angle / 180.0f);

    glm::vec3 arc;
    arc.x = (CosA + (1 - CosA) * x * x) * view.x
            + ((1 - CosA) * x * y - z * SinA) * view.y
            + ((1 - CosA) * x * z + y * SinA) * view.z;
    arc.y = ((1 - CosA) * x * y + z * SinA) * view.x
            + (CosA + (1 - CosA) * y * y) * view.y
            + ((1 - CosA) * y * z - x * SinA) * view.z;
    arc.z = ((1 - CosA) * x * z - y * SinA) * view.x
            + ((1 - CosA) * y * z + x * SinA) * view.y
            + (CosA + (1 - CosA) * z * z) * view.z;

    center = eye + arc;
    lookAt(eye, center, up);
}

void CBasicCamera::rotateViewUpBottom(float angle)
{
    glm::vec3 axisOfRotation = glm::normalize<float>( glm::cross<float>(center - eye, up) );
    rotateView(angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
}

void CBasicCamera::rotatePosition(float angle, float x, float y, float z)
{
    if (x == 0 && y == 0 && z == 0) {
        x = up.x;
        y = up.y;
        z = up.z;
    }
    eye -= center;
    glm::vec3 view = eye;

    float SinA = glm::sin<float>(glm::pi<float>() * angle / 180.0f);
    float CosA = glm::cos<float>(glm::pi<float>() * angle / 180.0f);

    glm::vec3 arc;
    arc.x = (CosA + (1 - CosA) * x * x) * view.x
            + ((1 - CosA) * x * y - z * SinA) * view.y
            + ((1 - CosA) * x * z + y * SinA) * view.z;
    arc.y = ((1 - CosA) * x * y + z * SinA) * view.x
            + (CosA + (1 - CosA) * y * y) * view.y
            + ((1 - CosA) * y * z - x * SinA) * view.z;
    arc.z = ((1 - CosA) * x * z - y * SinA) * view.x
            + ((1 - CosA) * y * z + x * SinA) * view.y
            + (CosA + (1 - CosA) * z * z) * view.z;

    eye = center + arc;
    lookAt(eye, center, up);
}

void CBasicCamera::rotatePositionUpBottom(float angle)
{
    glm::vec3 axisOfRotation = glm::normalize<float>( glm::cross<float>(center - eye, up) );
    rotatePosition(angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
}

void CBasicCamera::translate(const glm::vec3 &shift)
{
    eye += shift;
    center += shift;
    lookAt(eye, center, up);
}

void CBasicCamera::translate(float x, float y, float z)
{
    translate(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getDirection() const
{
    return glm::normalize(center - eye);
}

glm::mat4 CBasicCamera::getViewMatrix() const
{
    return viewMatrix;
}

glm::mat4 CBasicCamera::getProjectionMatrix() const
{
    return projectionMatrix;
}

glm::mat4 CBasicCamera::getViewProjectionMatrix() const
{
    return viewMatrix * projectionMatrix;
}

} // namespace core
