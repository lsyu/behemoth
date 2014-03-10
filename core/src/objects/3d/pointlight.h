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

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "basiclight.h"

namespace core {

class CLightFactory;

/**
 * @brief Точечтый источник освещения.
 */
class CPointLight : public CBasicLight
{
public:
    friend class CLightFactory;

    // AbstractLight interface
    virtual void setPosition(const glm::vec3 &position) override;
    virtual void setPosition(float x, float y, float z) override;
    virtual glm::vec3 getPosition() const override;

protected:
    CPointLight();
    virtual ~CPointLight();

private:
    glm::vec3 position;     //in world space
}; // class CPointLight

} // namespace core

#endif // POINTLIGHT_H
