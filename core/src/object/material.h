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

#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/glm.h"

namespace Core {

/**
 * @brief Предоставляет интерфейс к свойствам параметров материала.
 * @todo Сделать нормальное наследование, продумать интерфейс базового класса.
 * @todo Написать фабрику загрузки материала.
 */
class Material
{
public:

    /**
     * @enum Модель затенения
     */
    enum Shading {
        Phong = 0,      /**< По Фонгу */
        CoockTorrance   /**< По Куку-Торренсу */
    };

    Material() {}

    /**
     * @brief Конструктор материала с затенением по Фонгу.
     *
     * @param ambient коэффициент фонового освещения.
     * @param diffuse коэффициент диффузного освещения.
     * @param specular коэффициент зеркального освещения.
     */
    Material(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular);

    /**
     * @brief Конструктор материала с затенением по Куку-Торренсу.
     * @param roughness шероховатость поверхности (от 0 до 1).
     * @param refraction коэффициент отражения энергии.
     */
    Material(float roughness, float refraction);

    void setAmbient(const glm::vec4 &ambient);
    void setAmbient(float r, float g, float b, float a = 1.0f);
    glm::vec4 getAmbient() const;
    void setDiffuse(const glm::vec4 &diffuse);
    void setDiffuse(float r, float g, float b, float a = 1.0f);
    glm::vec4 getDiffuse() const;
    void setSpecular(const glm::vec4 &specular);
    void setSpecular(float r, float g, float b, float a = 1.0f);
    glm::vec4 getSpecular() const;
    void setRoughness(float roughness);
    float getRoughness() const;
    void setRefraction(float refraction);
    float getRefraction() const;
    Shading getShading() const;
    void setShading(Shading shading);

protected:
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float roughness;
    float refraction;
    Shading shading;
}; // class Material

} // namespace Core

#endif // MATERIAL_H
