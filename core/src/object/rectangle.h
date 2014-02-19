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

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "basic2dentity.h"

#include "core/ogl/vertexbufferobject.h"
#include "core/ogl/vertexarrayobject.h"

class CShader;

namespace core {

class CRectangle : public Basic2dEntity
{
public:
    CRectangle();
    /**
     * @brief Прямоугольник красного цвета с вершинами в точках (-1, -1) (-1, 1) (1, 1) (1, -1).
     */
    explicit CRectangle(const std::string &id);

    virtual ~CRectangle();

    virtual void paint() const override;
    virtual void setColor(const glm::vec3 &color);
    glm::vec3 getColor() const;
    virtual float getXMin() const override;
    virtual float getXMax() const override;
    virtual float getYMin() const override;
    virtual float getYMax() const override;

    virtual void onClicked(const CEventMouseClick &event) override;

    /**
     * @brief Установить координату X левого нижнего угла прямоугольника.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     */
    void setX(float x);
    /**
     * @brief Установить координату Y левого нижнего угла прямоугольника.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     */
    void setY(float y);
    /**
     * @brief Установить длину.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     * @note Длина  - неотрицательное значение!
     */
    void setWidth(float width);
    float getWidth() const;
    /**
     * @brief Установить высоту.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     * @note Высота - неотрицательное значение!
     */
    void setHeight(float height);
    float getHeight() const;
    /**
     * @brief Установить радиус скругления всех углов.
     * @note Длина радиуса - отношение к половине меньшей стороны прямоугольника.
     * @note Для радиуса верно: 0.0f=0%, 1.0f=100% от половины меньшей стороны прямоугольника.
     * @sa setRadiusOfA, setRadiusOfB, setRadiusOfC, setRadiusOfD
     */
    void setRadius(float radius);
    /**
     * @brief Получить среднее значение rA, rB, rC, rD
     */
    float getRadius() const;
    /**
     * @brief Установить радиус скругления угла при вершине A(нижний левый).
     */
    void setRadiusOfA(float rA);
    float getRadiusOfA() const;
    /**
     * @brief Установить радиус скругления угла при вершине B(верхний левый).
     */
    void setRadiusOfB(float rB);
    float getRadiusOfB() const;
    /**
     * @brief Установить радиус скругления угла при вершине C(верхний правый).
     */
    void setRadiusOfC(float rC);
    float getRadiusOfC() const;
    /**
     * @brief Установить радиус скругления угла при вершине D(нижний правый).
     */
    void setRadiusOfD(float rD);
    float getRadiusOfD() const;
    /**
     * @brief Установить толщину границы.
     */
    void setBorderWidth(float width);
    float getBorderWidth() const;
    /**
     * @brief Установить цвет границы
     */
    void setBorderColor(const glm::vec3 &color);
    glm::vec3 getBorderColor() const;
    /**
     * @brief Получение текстуры при помощи менеджера текстур.
     * @param name имя файла текстуры без расширения .dds
     */
    void setTexture(const std::string &name);
    std::string getTexture() const;
    /**
     * @brief Получение прозрачности.
     *
     * @note 0 - полностью прозрачный, 1 - полностью непрозрачный.
     */
    void setAlpha(float alpha);
    float getAlpha() const;

protected:
    virtual void configure() override;

    /**
     * @brief Содержит ли фигура точку point
     */
    bool contains(const glm::vec2 &point) const;


    CShader *shader; // Получаю с фабрики, не надо чистить память
    CVertexArrayObject vao;
    CVertexBufferObject vertex;
    CVertexBufferObject color;
    CVertexBufferObject uv;

    float aspect;
    float x;
    float y;
    float width;
    float height;
    float rA;
    float rB;
    float rC;
    float rD;
    float alpha;
    uint texture;
    std::string textureName;
    Border border;
}; //class Rectangle

} // namespace Core

#endif // RECTANGLE_H
