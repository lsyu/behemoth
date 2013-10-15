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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "entity.h"

#include "core/ogl/shader.h"
#include "core/ogl/vertexbufferobject.h"
#include "core/ogl/vertexarrayobject.h"

namespace Core {

/**
 * @brief Треугольник.
 * @todo Наследование от Entity. Разорбраться с материалом.
 */
class Triangle : public Core::Entity
{
public:
    Triangle();
    /**
     * @brief Треугольник красного цвета с вершинами в точках (-1, -1) (0, 1) (1, -1).
     */
    explicit Triangle(const std::string &id);

    void setPoint1(const glm::vec2 &p1);
    glm::vec2 getPoint1() const;
    void setPoint2(const glm::vec2 &p2);
    glm::vec2 getPoint2() const;
    void setPoint3(const glm::vec2 &p3);
    glm::vec2 getPoint3() const;

    void setColor1(const glm::vec3 &c1);
    glm::vec3 getColor1() const;
    void setColor2(const glm::vec3 &c2);
    glm::vec3 getColor2() const;
    void setColor3(const glm::vec3 &c3);
    glm::vec3 getColor3() const;

    virtual void paint() const;
    virtual void setColor(const glm::vec3 &color);


//    /**
//     * @brief Конструирование треугольника по 3м точкам.
//     * @param point1 Точка 1.
//     * @param point2 Точка 2.
//     * @param point3 Точка 3.
//     */
//    Triangle(const glm::vec2 &point1, const glm::vec2 &point2, const glm::vec2 &point3);
//    /**
//     * @brief Конструирование треугольника по 3м точкам с однородной заливкой.
//     * @param point1 Точка 1.
//     * @param point2 Точка 2.
//     * @param point3 Точка 3.
//     * @param color цвет заливки (rgb).
//     */
//    Triangle(const glm::vec2 &point1, const glm::vec2 &point2, const glm::vec2 &point3,
//            const glm::vec3 &color);
//    /**
//     * @brief Конструирование треугольника по 3м точкам с однородной заливкой.
//     * @param point1 Точка 1.
//     * @param color1 цвет заливки точки 1 (rgb).
//     * @param point2 Точка 2.
//     * @param color1 цвет заливки точки 2 (rgb).
//     * @param point3 Точка 3.
//     * @param color1 цвет заливки точки 3 (rgb).
//     */
//    Triangle(const glm::vec2 &point1, const glm::vec3 &color1, const glm::vec2 &point2,
//           const glm::vec3 &color2, const glm::vec2 &point3, const glm::vec3 color3);
////    /**
////     * @brief Конструирование треугольника по 3м точкам с материалом material.
////     * @param point1 Точка 1.
////     * @param point2 Точка 2.
////     * @param point3 Точка 3.
////     * @param material материал треугольника.
////     */
////    Triangle(const glm::vec2 &point1, const glm::vec2 &point2, const glm::vec2 &point3,
////            const Material &material);
    /**
     * @brief Деструктор
     **/
    ~Triangle();

protected:
    virtual void configure();

private:
    Shader shader;
    VertexArrayObject vao;
    VertexBufferObject vertex;
    VertexBufferObject color;
}; // class Triangle

} // namespace Core

#endif // TRIANGLE_H
