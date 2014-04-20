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

namespace bhm {

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

    void setColor(const glm::vec3 &color); // TODO: enum of color!
    glm::vec3 getColor() const;

    bool operator ==(const CFont &other) const;
    bool operator <(const CFont &other) const;

private:
    std::string m_name;           /**< Название шрифта. */
    float m_height;               /**< Высота шрифта. @n
                                    * Отображаемая высота (относительная)
                                    */
    glm::vec3 m_color;            /**< Цвет шрифта */
}; // class CFont

} // namespace behemoth

#endif // FONT_H
