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

#include "camera.h"
#include "../constants.h"
#include "glm/ext.h"

namespace Core {

using namespace glm;

void Camera::initCameraPerspective(float widthOfVieport, float heightOfVieport, float nearPlane, float farPlane)
{
    if(heightOfVieport == 0)
        heightOfVieport = 1;
    float aspectRatio;
    aspectRatio =  widthOfVieport /  heightOfVieport;

    projectionMatrix = perspective(45.0f, aspectRatio, nearPlane, farPlane);

    eye = glm::vec3(0.0f, 0.0f, 1.0f);
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(eye, center, up);
}

void Camera::initCameraOrtho(float left, float right, float bottom, float top, float near, float far)
{
    projectionMatrix = ortho(left, right, bottom, top, near, far);

    eye = glm::vec3(0.0f, 0.0f, 1.0f);
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(eye, center, up);
}

void Camera::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
    viewMatrix = glm::lookAt(eye, center, up);
}

void Camera::setPosition(const vec3 &position)
{
    eye = position;
    lookAt(eye, center, up);
}

void Camera::setPosition(float x, float y, float z)
{
    setPosition(vec3(x, y, z));
}

vec3 Camera::getPosition() const
{
    return eye;
}

void Camera::setCenter(const vec3 &center)
{
    this->center = center;
    lookAt(eye, center, up);
}

void Camera::setCenter(float x, float y, float z)
{
    setPosition(vec3(x, y, z));
}

vec3 Camera::getCenter() const
{
    return center;
}

void Camera::rotateView(float angle, float x, float y, float z)
{
    if (x == 0 && y == 0 && z == 0) {
        x = up.x;
        y = up.y;
        z = up.z;
    }
    center -= eye;
    vec3 view = center;

    float SinA = sin<float>(PI * angle / 180.0f);
    float CosA = cos<float>(PI * angle / 180.0f);

    vec3 arc;
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
    this->lookAt(eye, center, up);
}

void Camera::rotateViewUpBottom(float angle)
{
    vec3 axisOfRotation = normalize<float>( cross<float>(center - eye, up) );
    this->rotateView(angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
}

void Camera::rotatePosition(float angle, float x, float y, float z)
{
    if (x == 0 && y == 0 && z == 0) {
        x = up.x;
        y = up.y;
        z = up.z;
    }
    eye -= center;
    vec3 view = eye;

    float SinA = sin<float>(PI * angle / 180.0f);
    float CosA = cos<float>(PI * angle / 180.0f);

    vec3 arc;
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
    this->lookAt(eye, center, up);
}

void Camera::rotatePositionUpBottom(float angle)
{
    vec3 axisOfRotation = normalize<float>( cross<float>(center - eye, up) );
    this->rotatePosition(angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
}

void Camera::translate(const vec3 &shift)
{
    eye += shift;
    center += shift;
    this->lookAt(eye, center, up);
}

void Camera::translate(float x, float y, float z)
{
    translate(vec3(x, y, z));
}

vec3 Camera::getDirection() const
{
    return normalize(center - eye);
}

mat4 Camera::getViewMatrix() const
{
    return viewMatrix;
}

mat4 Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

mat4 Camera::getViewProjectionMatrix() const
{
    return viewMatrix * projectionMatrix;
}

} // namespace Core
