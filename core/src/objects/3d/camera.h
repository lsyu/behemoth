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

#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.h"

namespace core {

/**
 * @brief Камера.
 *
 * В зависимости от типа матрицы проекции камера может быть
 * - перспективной
 * - ортогональной
 */
class Camera
{
public:
    
    /**
     * @brief Перспективная проекция.
     *
     * Матрица проекции устанавливается в перспективную.
     *
     * @param widthOfVieport ширина зоны просмотра (viewport).
     * @param heightOfVieport высота зоны просмотра (viewport).
     * @param nearPlane ближняя плоскость отсечения.
     * @param farPlane дальняя плоскость отсечения.
     */
    void initCameraPerspective(float widthOfVieport, float heightOfVieport, float nearPlane = 1.0f, float farPlane = 100.0f);
    
    /**
     * @brief Ортогональная проекция.
     *
     * Матрица проекции устанавливается в ортогональную.
     *
     * @param left левая граница отсечения.
     * @param right правая граница отсечения.
     * @param bottom нижняя граница отсечения.
     * @param top верхняя граница отсечения.
     * @param near ближняя граница отсечения.
     * @param far дальняя граница отсечения.
     */
    void initCameraOrtho(float left, float right, float bottom, float top, float near, float far);

    /**
     * @brief Устанавливает преобразования модельно-видовой матрицы.
     * @param eye Положение наблюдателя.
     * @param center Точка направления взгляда.
     * @param up Направление вверх относительно направления взгляда.
     */
    void lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

    void setPosition(const glm::vec3 &position);
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition() const;
    void setCenter(const glm::vec3 &center);
    void setCenter(float x, float y, float z);
    glm::vec3 getCenter() const;

    /**
     * @brief Вращение взгляда камеры.
     * @param angle угол поворота в градусах.
     * @param x координата X вектора, вокруг которого будет вращаться камера.
     * @param y координата Y вектора, вокруг которого будет вращаться камера.
     * @param z координата Z вектора, вокруг которого будет вращаться камера.
     */
    void rotateView(float angle, float x = 0.0f, float y = 0.0f, float z = 0.0f);
    
    /**
     * @brief Вращение взгляда камеры "вверх-вниз" относительно ее текущего положения.
     * @param angle угол поворота в градусах.
     */
    void rotateViewUpBottom(float angle);
    
    /**
     * @brief Вращение позиции положения наблюдателя.
     * @param angle угол поворота в градусах.
     * @param x координата X вектора, вокруг которого будет вращаться камера.
     * @param y координата Y вектора, вокруг которого будет вращаться камера.
     * @param z координата Z вектора, вокруг которого будет вращаться камера.
     */
    void rotatePosition(float angle, float x = 0.0f, float y = 0.0f, float z = 0.0f);
    
    /**
     * @brief Вращение позиции наблюдателя "вверх-вниз" относительно его текущего положения.
     * @param angle угол поворота в градусах.
     */
    void rotatePositionUpBottom(float angle);
    
    /**
     * @brief Перемещение камеры.
     * @param shift вектор смещения.
     */
    void translate(const glm::vec3 &shift);
    
    /**
     * @brief Перемещение камеры.
     * @param x координата X вектора смещения.
     * @param y координата Y вектора смещения.
     * @param z координата Z вектора смещения.
     */
    void translate(float x, float y, float z);

    glm::vec3 getDirection() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;

private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
}; // class Camera

} // namespace Core

#endif // CAMERA_H
