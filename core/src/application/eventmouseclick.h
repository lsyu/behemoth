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

#ifndef EVENTMOUSECLICK_H
#define EVENTMOUSECLICK_H

#include "abstractevent.h"

#include "glm/glm.h"

namespace core {

/**
 * @brief Событие клика мыши
 */
class CEventMouseClick : public AbstractEvent
{
public:
    explicit CEventMouseClick(int x = 0, int y = 0);
    virtual ~CEventMouseClick();

    glm::vec2 getCoordinates() const;
    float getX() const;
    float getY() const;


private:
    float x;    /**< Абсцисса точки клика. В относительныйх величинах [-1..1] */
    float y;    /**< Оордината точки клика. В относительныйх величинах [-1..1] */
}; // class CEventMouseClick

} // namespace core

#endif // EVENTMOUSECLICK_H
