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

#ifndef EVENTMOUSECLICK_H
#define EVENTMOUSECLICK_H

#include "abstractevent.h"

#include "glm/glm.h"

namespace behemoth {

/**
 * @brief Клавиши мыши
 */
enum class EMouseButton: unsigned char {
    left,   /**< Левая.  */
    right,  /**< Правая. */
    middle  /**< Средняя(колесико). */
}; // enum EMouseButton

/**
 * @brief Состояние события
 */
enum class EMouseState: unsigned char {
    down,   /**< Нажата */
    up      /**< Отпущена */
}; // enum EMouseState

/**
 * @brief Событие клика мыши
 */
class CEventMouseClick : public AbstractEvent
{
public:
    explicit CEventMouseClick(int x = 0, int y = 0, EMouseButton btn = EMouseButton::left,
                              EMouseState state = EMouseState::down);
    virtual ~CEventMouseClick();

    glm::vec2 getCoordinates() const;
    float getX() const;
    float getY() const;
    EMouseButton getMouseButton() const;
    EMouseState getMouseState() const;


private:
    float x;            /**< Абсцисса точки клика. В относительныйх величинах [-1..1] */
    float y;            /**< Оордината точки клика. В относительныйх величинах [-1..1] */
    EMouseButton btn;   /**< Кнопка */
    EMouseState state;  /**< Состояние */
}; // class CEventMouseClick

} // namespace behemoth

#endif // EVENTMOUSECLICK_H
