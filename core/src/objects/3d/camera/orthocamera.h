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

#ifndef ORTHOCAMERA_H
#define ORTHOCAMERA_H

#include "basiccamera.h"

namespace behemoth {

/**
 * @brief Камера с ортогональной проекцией.
 */
class COrthoCamera : public CBasicCamera
{
public:
    /**
     * @brief Ортогональная проекция.
     *
     * Матрица проекции устанавливается в ортогональную.
     *
     * @param left левая граница отсечения.
     * @param right правая граница отсечения.
     * @param bottom нижняя граница отсечения.
     * @param top верхняя граница отсечения.
     * @param near ближняя граница отсечения.
     * @param far дальняя граница отсечения.
     */
    COrthoCamera(float left, float right, float bottom, float top, float near, float far);
};

} // namespace behemoth

#endif // ORTHOCAMERA_H
