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

#ifndef CBASICLIGHT_H
#define CBASICLIGHT_H

#include "abstractlight.h"

namespace bhm {

class CLightFactory;

/**
 * @brief Базовый класс источника освещения.
 */
class CBasicLight : public  AbstractLight
{
public:
    friend class CLightFactory;

    // AbstractLight interface
    virtual void setAmbient(const glm::vec3 &ambient) override;
    virtual void setAmbient(float r, float g, float b) override;
    virtual glm::vec3 getAmbient() const override;
    virtual void setDiffuse(const glm::vec3 &diffuse) override;
    virtual void setDiffuse(float r, float g, float b) override;
    virtual glm::vec3 getDiffuse() const override;
    virtual void setSpecular(const glm::vec3 &specular) override;
    virtual void setSpecular(float r, float g, float b) override;
    virtual glm::vec3 getSpecular() const override;

protected:
    CBasicLight();
    virtual ~CBasicLight();
private:
    glm::vec3 m_ambient;  /**< Цвет фонового излучения источника света. */
    glm::vec3 m_diffuse;  /**< Цвет рассеного излучения источника света. */
    glm::vec3 m_specular; /**< Цвет зеркального излучения источника света. */
}; // class CBasicLight

} // namespace behemoth

#endif // CBASICLIGHT_H
