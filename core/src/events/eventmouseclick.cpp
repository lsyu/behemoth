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

#include "eventmouseclick.h"
#include "core/application/application.h"

namespace behemoth {

CEventMouseClick::CEventMouseClick(int x, int y, EMouseButton btn, EMouseState state) : AbstractEvent(),
    m_x(), m_y(), m_btn(btn), m_state(state)
{
    glm::vec2 coord = CApplication::getInstance()->getRelativeCoordinate(x, y);
    this->m_x = coord.x;
    this->m_y = -coord.y;
}

CEventMouseClick::~CEventMouseClick()
{
}

glm::vec2 CEventMouseClick::getCoordinates() const
{
    return glm::vec2(m_x, m_y);
}

float CEventMouseClick::getX() const
{
    return m_x;
}

float CEventMouseClick::getY() const
{
    return m_y;
}

EMouseButton CEventMouseClick::getMouseButton() const
{
    return m_btn;
}

EMouseState CEventMouseClick::getMouseState() const
{
    return m_state;
}

} // namespace behemoth
