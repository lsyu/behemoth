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

#ifndef BASICCAMERA_H
#define BASICCAMERA_H

#include "abstractcamera.h"

namespace core {

/**
 * @brief Базовый класс камеры, реализующий методы, одинаковые для всех камер.
 */
class CBasicCamera : public AbstractCamera
{
public:
    CBasicCamera();

    // AbstractCamera interface
    virtual void lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) override;
    virtual void setEye(const glm::vec3 &eye) override;
    virtual void setEye(float x, float y, float z) override;
    virtual glm::vec3 getEye() const override;
    virtual void setCenter(const glm::vec3 &center) override;
    virtual void setCenter(float x, float y, float z) override;
    virtual glm::vec3 getCenter() const override;
    virtual void setUp(const glm::vec3 &up) override;
    virtual void setUp(float x, float y, float z) override;
    virtual glm::vec3 getUp() const override;
    virtual void rotateView(float angle, float x, float y, float z) override;
    virtual void rotateViewUpBottom(float angle) override;
    virtual void rotatePosition(float angle, float x, float y, float z) override;
    virtual void rotatePositionUpBottom(float angle) override;
    virtual void translate(const glm::vec3 &shift) override;
    virtual void translate(float x, float y, float z) override;
    virtual glm::vec3 getDirection() const override;
    virtual glm::mat4 getViewMatrix() const override;
    virtual glm::mat4 getProjectionMatrix() const override;
    virtual glm::mat4 getViewProjectionMatrix() const override;

protected:
    glm::vec3 eye;              /**< Положение камеры. */
    glm::vec3 center;           /**< Точка, куда смотрит камера. */
    glm::vec3 up;               /**< "Верх" камеры. */

    glm::mat4 viewMatrix;       /**< Матрица вида. */
    glm::mat4 projectionMatrix; /**< Матрица проекции. */
}; // class CBasicCamera

} // namespace core

#endif // BASICCAMERA_H
