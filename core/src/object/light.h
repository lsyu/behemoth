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

#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.h"
#include "camera.h"

namespace core {

/**
 * @brief Источник света.
 *
 * Все источники света являются направленными. Так решено в связи с более низкими
 * расходами при обсчете карт теней по сравнению с точечными источниками света.
 * Скорее всего в дальнейшем надо будет переработать с учетом точечных
 * источников света.
 */
class Light
{
public:

    /**
     * @brief Инициализация источника света.
     *
     * Инициализация камеры для отрисовки карты теней. Установка позиции и направления освещения.
     *
     * @param position позиция наблюдателя.
     * @param center точка взгляда наблюдателя.
     * @param up вектор, указывающий направление вверх.
     * @param left левая граница отсечения.
     * @param right правая граница отсечения.
     * @param bottom нижняя граница отсечения.
     * @param top верхняя граница отсечения.
     * @param near ближняя граница отсечения.
     * @param far дальняя граница отсечения.
     */
    void initLight(const glm::vec3 &position,
                   const glm::vec3 &center,
                   const glm::vec3 &up,
                   float left, float right,
                   float bottom, float top,
                   float near, float far);

    /**
     * @brief Вращение направления источника света.
     * @param angle угол поворота в градусах.
     * @param x координата X вектора, вокруг которого будет вращаться источник света.
     * @param y координата Y вектора, вокруг которого будет вращаться источник света.
     * @param z координата Z вектора, вокруг которого будет вращаться источник света.
     */
    void rotateView(float angle, float x = 0, float y = 0, float z = 0);

    /**
     * @brief Вращение взгляда источника света "вверх-вниз" относительно ее текущего положения.
     * @param angle угол поворота в градусах.
     */
    void rotateViewUpBottom(float angle);

    /**
     * @brief Вращение позиции положения источника света.
     * @param angle угол поворота в градусах.
     * @param x координата X вектора, вокруг которого будет вращаться источник света.
     * @param y координата Y вектора, вокруг которого будет вращаться источник света.
     * @param z координата Z вектора, вокруг которого будет вращаться источник света.
     */
    void rotatePosition(float angle, float x = 0, float y = 0, float z = 0);

    /**
     * @brief Вращение позиции источника света "вверх-вниз" относительно его текущего положения.
     * @param angle угол поворота в градусах.
     */
    void rotatePositionUpBottom(float angle);

    /**
     * @brief Перемещение источника света.
     * @param shift вектор смещения.
     */
    void translate(const glm::vec3 &shift);

    /**
     * @brief Перемещение источник света.
     * @param x координата X вектора смещения.
     * @param y координата Y вектора смещения.
     * @param z координата Z вектора смещения.
     */
    void translate(float x, float y, float z);

    void setPosition(const glm::vec3 &position);
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition() const;
    void setDirection(float x, float y, float z);
    void setDirection(const glm::vec3 &direction);
    glm::vec3 getDirection() const;
    Camera getCameraOfLight() const;

private:
    glm::vec3 position;     //in world space
    glm::vec3 direction;    //in world space
    glm::vec3 up;

    Camera camLight;        //камера, с которой рендерится эффекты освещения ( для тени, короче :) )
}; // class Light

} // namespace Core

#endif // LIGHT_H
