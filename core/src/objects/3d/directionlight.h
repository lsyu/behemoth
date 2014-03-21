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

#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include "pointlight.h"

namespace core {

class CLightFactory;

/**
 * @brief Направленный источнк освещения.
 */
class CDirectionLight : public CPointLight
{
public:
    friend class CLightFactory;

    /**
     * @brief Установить направление источника света.
     */
    virtual void setDirection(const glm::vec3 &direction);
    /**
     * @brief Установить направление источника света.
     */
    virtual void setDirection(float x, float y, float z);
    /**
     * @brief Получить направление источника света.
     */
    virtual glm::vec3 getDirection() const;

protected:
    CDirectionLight();
    virtual ~CDirectionLight();

private:
    glm::vec3 mDirection;    //in world space
}; // class CDirectionLight

} // namespace core

#endif // DIRECTIONLIGHT_H
