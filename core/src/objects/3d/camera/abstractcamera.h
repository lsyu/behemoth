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

#ifndef ABSTRACTCAMERA_H
#define ABSTRACTCAMERA_H

#include "glm/glm.h"

namespace bhm {

class CCameraFactory;

/**
 * @brief Интерфейс камеры
 */
class AbstractCamera
{
public:
    friend class CCameraFactory;

    /**
     * @brief Устанавливает преобразования модельно-видовой матрицы для установки положения камеры.
     * @param eye Положение наблюдателя.
     * @param center Точка направления взгляда.
     * @param up Направление вверх относительно направления взгляда.
     */
    virtual void lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) = 0;

    /**
     * @brief Установить положение камеры.
     * @param eye позиция взгляда (т.е. точка, откуда смотрит наблюдатель).
     */
    virtual void setEye(const glm::vec3 &eye) = 0;

    /**
     * @brief Установить положение камеры.
     * @param x координата x позиции взгляда (т.е. точка, откуда смотрит наблюдатель).
     * @param y координата y позиции взгляда (т.е. точка, откуда смотрит наблюдатель).
     * @param z координата z позиции взгляда (т.е. точка, откуда смотрит наблюдатель).
     */
    virtual void setEye(float x, float y, float z) = 0;

    /**
     * @brief Получить положение камеры.
     */
    virtual glm::vec3 getEye() const = 0;

    /**
     * @brief Установить точку направления взгляда.
     * @param center направление взгляда (т.е. точка, куда смотрит наблюдатель).
     */
    virtual void setCenter(const glm::vec3 &center) = 0;

    /**
     * @brief Установить точку направления взгляда.
     * @param x координата x точки направления взгляда (т.е. точки, куда смотрит наблюдатель).
     * @param y координата y точки направления взгляда (т.е. точки, куда смотрит наблюдатель).
     * @param z координата z точки направления взгляда (т.е. точки, куда смотрит наблюдатель).
     */
    virtual void setCenter(float x, float y, float z) = 0;

    /**
     * @brief Получить точку направления камеры.
     */
    virtual glm::vec3 getCenter() const = 0;

    /**
     * @brief Установить направление "верха".
     * @param up направление верха (т.е. вектор, перпендикулярный направлению взгляда).
     */
    virtual void setUp(const glm::vec3 &up) = 0;

    /**
     * @brief Установить направление "верха".
     * @param x координата x направления верха (т.е. вектора, перпендикулярного направлению взгляда).
     * @param y координата y направления верха (т.е. вектора, перпендикулярного направлению взгляда).
     * @param z координата z направления верха (т.е. вектора, перпендикулярного направлению взгляда).
     */
    virtual void setUp(float x, float y, float z) = 0;

    /**
     * @brief Получить направление верха.
     */
    virtual glm::vec3 getUp() const = 0;

    /**
     * @brief Вращение взгляда камеры.
     * @param angle угол поворота в градусах.
     * @param x координата X вектора, вокруг которого будет вращаться камера.
     * @param y координата Y вектора, вокруг которого будет вращаться камера.
     * @param z координата Z вектора, вокруг которого будет вращаться камера.
     */
    virtual void rotateView(float angle, float x = 0.0f, float y = 0.0f, float z = 0.0f) = 0;

    /**
     * @brief Вращение взгляда камеры "вверх-вниз" относительно ее текущего положения.
     * @param angle угол поворота в градусах.
     */
    virtual void rotateViewUpBottom(float angle) = 0;

    /**
     * @brief Вращение позиции положения наблюдателя.
     * @param angle угол поворота в градусах.
     * @param x координата X вектора, вокруг которого будет вращаться камера.
     * @param y координата Y вектора, вокруг которого будет вращаться камера.
     * @param z координата Z вектора, вокруг которого будет вращаться камера.
     */
    virtual void rotatePosition(float angle, float x = 0.0f, float y = 0.0f, float z = 0.0f) = 0;

    /**
     * @brief Вращение позиции наблюдателя "вверх-вниз" относительно его текущего положения.
     * @param angle угол поворота в градусах.
     */
    virtual void rotatePositionUpBottom(float angle) = 0;

    /**
     * @brief Перемещение камеры.
     * @param shift вектор смещения.
     */
    virtual void translate(const glm::vec3 &shift) = 0;

    /**
     * @brief Перемещение камеры.
     * @param x координата X вектора смещения.
     * @param y координата Y вектора смещения.
     * @param z координата Z вектора смещения.
     */
    virtual void translate(float x, float y, float z) = 0;

    virtual glm::vec3 getDirection() const = 0;
    virtual glm::mat4 getViewMatrix() const = 0;
    virtual glm::mat4 getProjectionMatrix() const = 0;
    virtual glm::mat4 getViewProjectionMatrix() const = 0;
    virtual glm::mat3 getNormalMatrix(const glm::mat4 &model) const = 0;

protected:
    virtual ~AbstractCamera() {}
}; // class AbstractCamera

} // namespace behemoth

#endif // ABSTRACTCAMERA_H
