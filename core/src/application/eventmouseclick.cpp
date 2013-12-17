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

#include "eventmouseclick.h"
#include "application.h"

namespace core {

CEventMouseClick::CEventMouseClick(int x, int y, EMouseButton btn, EMouseState state) : AbstractEvent(),
    x(), y(), btn(btn), state(state)
{
    glm::vec2 coord = CApplication::getInstance()->getRelativeCoordinate(x, y);
    this->x = coord.x;
    this->y = -coord.y;
}

CEventMouseClick::~CEventMouseClick()
{
}

glm::vec2 CEventMouseClick::getCoordinates() const
{
    return glm::vec2(x, y);
}

float CEventMouseClick::getX() const
{
    return x;
}

float CEventMouseClick::getY() const
{
    return y;
}

EMouseButton CEventMouseClick::getMouseButton() const
{
    return btn;
}

EMouseState CEventMouseClick::getMouseState() const
{
    return state;
}

} // namespace core
