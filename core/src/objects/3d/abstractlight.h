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

#ifndef ABSTRACTLIGHT_H
#define ABSTRACTLIGHT_H

#include "glm/glm.h"

namespace behemoth {

class CLightFactory;

/**
 * @brief Интерфейс источника освещения.
 */
class AbstractLight
{
public:
    friend class CLightFactory;

    /**
     * @brief Установить положение источника света.
     */
    virtual void setPosition(const glm::vec3 &position) = 0;

    /**
     * @brief Установить положение источника света.
     */
    virtual void setPosition(float x, float y, float z) = 0;

    /**
     * @brief Получить положение источника света.
     */
    virtual glm::vec3 getPosition() const = 0;

    /**
     * @brief Установить цвет фонового излучения.
     */
    virtual void setAmbient(const glm::vec3 &ambient) = 0;

    /**
     * @brief Установить цвет фонового излучения.
     */
    virtual void setAmbient(float r, float g, float b) = 0;

    /**
     * @brief Получить цвет фонового излучения.
     */
    virtual glm::vec3 getAmbient() const = 0;

    /**
     * @brief Установить цвет  рассеного излучения.
     */
    virtual void setDiffuse(const glm::vec3 &diffuse) = 0;

    /**
     * @brief Установить цвет  рассеного излучения.
     */
    virtual void setDiffuse(float r, float g, float b) = 0;

    /**
     * @brief Получить цвет  рассеного излучения.
     */
    virtual glm::vec3 getDiffuse() const = 0;

    /**
     * @brief Установить цвет зеркального излучения.
     */
    virtual void setSpecular(const glm::vec3 &specular) = 0;

    /**
     * @brief Установить цвет зеркального излучения.
     */
    virtual void setSpecular(float r, float g, float b) = 0;

    /**
     * @brief Получить цвет зеркального излучения.
     */
    virtual glm::vec3 getSpecular() const = 0;
protected:
    AbstractLight() {}
    virtual ~AbstractLight() {}
};

} // namespace behemoth

#endif // ABSTRACTLIGHT_H
