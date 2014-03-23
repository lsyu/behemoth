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

#ifndef FONT_H
#define FONT_H

#include <string>
#include "glm/glm.h"

namespace behemoth {

/**
 * @brief Перечисления выравнивания по вертикали
 */
enum class EVerticalAlign : unsigned char {
    Top = 0,    /**< По верхнему краю */
    Center = 1, /**< По центру */
    Bottom = 2  /**< По нижнему краю */
}; // enum EVerticalAlign

/**
 * @brief Перечисления выравнивания по горизонтали
 */
enum class EHorizontalAlign : unsigned char {
    Left = 0,   /**< По левому краю */
    Center = 1, /**< По центру */
    Right = 2   /**< По правому краю */
}; // enum EVerticalAlign

/**
 * @brief Шрифт
 *
 * Содержит название шрифта(в каталоге, указанном в файле конфигурации), высоту шрифта,
 * а также информацию о выравнивании по вертикали и по горизонтали.
 */
class CFont
{
public:
    /**
     * @brief Конструирование шрифта name высотой height
     */
    CFont(const std::string &name, int height);
    ~CFont();

    void setName(const std::string &name);
    std::string getName() const;

    void setHeight(float height);
    float getHeight() const;

    static void setQuantity(int _quantity);
    static int getQuantity();

    void setVericalAlign(EVerticalAlign vAlign);
    EVerticalAlign getVerticalAlign() const;

    void setHorizontalAlign(EHorizontalAlign hAlign);
    EHorizontalAlign getHorizontalAlign() const;

    void setColor(const glm::vec3 &color); // TODO: enum of color!
    glm::vec3 getColor() const;

private:
    static int quantity;        /**< Качество шрифта. @n
                                  * Настоящая высота шрифта при загрузке(в пикселях).
                                  */
    std::string name;           /**< Название шрифта. */
    float height;               /**< Высота шрифта. @n
                                  * Отображаемая высота (оттносительная)
                                  */
    EVerticalAlign vAlign;      /**< Выравнивание по вертикали */
    EHorizontalAlign hAlign;    /**< Выравнивание по горизонтали */
    glm::vec3 color;            /**< Цвет шрифта */
}; // class CFont

} // namespace behemoth

#endif // FONT_H
