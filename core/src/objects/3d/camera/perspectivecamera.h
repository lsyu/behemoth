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

#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "basiccamera.h"

namespace behemoth {

/**
 * @brief Камера с перспективной проекцией.
 */
class CPerspectiveCamera : public CBasicCamera
{
public:
    /**
     * @brief Перспективная проекция.
     *
     * Матрица проекции устанавливается в перспективную.
     *
     * @param widthOfVieport ширина зоны просмотра (viewport).
     * @param heightOfVieport высота зоны просмотра (viewport).
     * @param nearPlane ближняя плоскость отсечения.
     * @param farPlane дальняя плоскость отсечения.
     */
    CPerspectiveCamera(float widthOfVieport, float heightOfVieport, float fov = 45.0f, float nearPlane = 1.0f, float farPlane = 100.0f);
}; // class CPerspectiveCamera

} // namespace behemoth

#endif // PERSPECTIVECAMERA_H
