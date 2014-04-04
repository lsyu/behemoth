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

#include "orthocamera.h"

#include "glm/ext.hpp"

namespace behemoth {

COrthoCamera::COrthoCamera(float left, float right, float bottom, float top, float near, float far)
    : CBasicCamera()
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
    m_viewMatrix = glm::lookAt(m_eye, m_center, m_up);
}

} // namespace behemoth
