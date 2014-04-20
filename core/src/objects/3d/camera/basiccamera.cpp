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

#include "basiccamera.h"

#include "glm/gtc/constants.hpp"
#include "glm/ext.hpp"

namespace bhm {

CBasicCamera::CBasicCamera() : AbstractCamera(), m_eye(0.0f, 0.0f, 1.0f), m_center(0.0f, 0.0f, 0.0f),
    m_up(0.0f, 1.0f, 0.0f), m_viewMatrix(), m_projectionMatrix()
{
}

void CBasicCamera::lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up)
{
    this->m_eye = eye;
    this->m_center = center;
    this->m_up = up;
    m_viewMatrix = glm::lookAt(eye, center, up);
}

void CBasicCamera::setEye(const glm::vec3 &eye)
{
    this->m_eye = eye;
    lookAt(eye, m_center, m_up);
}

void CBasicCamera::setEye(float x, float y, float z)
{
    setEye(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getEye() const
{
    return m_eye;
}

void CBasicCamera::setCenter(const glm::vec3 &center)
{
    this->m_center = center;
    lookAt(m_eye, center, m_up);
}

void CBasicCamera::setCenter(float x, float y, float z)
{
    setCenter(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getCenter() const
{
    return m_center;
}

void CBasicCamera::setUp(const glm::vec3 &up)
{
    this->m_up = up;
    lookAt(m_eye, m_center, up);
}

void CBasicCamera::setUp(float x, float y, float z)
{
    setUp(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getUp() const
{
    return m_up;
}

void CBasicCamera::rotateView(float angle, float x, float y, float z)
{
    if (x == 0 && y == 0 && z == 0) {
        x = m_up.x;
        y = m_up.y;
        z = m_up.z;
    }
    m_center -= m_eye;
    glm::vec3 view = m_center;

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

    m_center = m_eye + arc;
    lookAt(m_eye, m_center, m_up);
}

void CBasicCamera::rotateViewUpBottom(float angle)
{
    glm::vec3 axisOfRotation = glm::normalize<float>( glm::cross<float>(m_center - m_eye, m_up) );
    rotateView(angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
}

void CBasicCamera::rotatePosition(float angle, float x, float y, float z)
{
    if (x == 0 && y == 0 && z == 0) {
        x = m_up.x;
        y = m_up.y;
        z = m_up.z;
    }
    m_eye -= m_center;
    glm::vec3 view = m_eye;

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

    m_eye = m_center + arc;
    lookAt(m_eye, m_center, m_up);
}

void CBasicCamera::rotatePositionUpBottom(float angle)
{
    glm::vec3 axisOfRotation = glm::normalize<float>( glm::cross<float>(m_center - m_eye, m_up) );
    rotatePosition(angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
}

void CBasicCamera::translate(const glm::vec3 &shift)
{
    m_eye += shift;
    m_center += shift;
    lookAt(m_eye, m_center, m_up);
}

void CBasicCamera::translate(float x, float y, float z)
{
    translate(glm::vec3(x, y, z));
}

glm::vec3 CBasicCamera::getDirection() const
{
    return glm::normalize(m_center - m_eye);
}

glm::mat4 CBasicCamera::getViewMatrix() const
{
    return m_viewMatrix;
}

glm::mat4 CBasicCamera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}

glm::mat4 CBasicCamera::getViewProjectionMatrix() const
{
    return m_viewMatrix * m_projectionMatrix;
}

glm::mat3 CBasicCamera::getNormalMatrix(const glm::mat4 &model) const
{
    glm::mat4 modelViewMatrix = m_viewMatrix * model;
    return glm::inverseTranspose(glm::mat3(modelViewMatrix));

}

} // namespace behemoth
