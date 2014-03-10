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

#ifndef LIGHTFACTORY_H
#define LIGHTFACTORY_H

#include "pointlight.h"
#include "directionlight.h"

#include <string>
#include <map>

namespace core {

class __CLightFactoryImplDel;

/**
 * @brief Тип источника освещения
 */
enum class ELightType: unsigned char {
    point,      /**< Точечный.  */
    direction  /**< Направленный. */
}; // enum EMouseButton

/**
 * @brief Фабрика загрузки источников освещения.
 */
class CLightFactory
{
public:
    friend class __CLightFactoryImplDel;

    /**
     * @brief Получить экземпляр фабрики источников освещения.
     * @return экземпляр фабрики источников освещения.
     */
    static CLightFactory* getInstance();

    /**
     * @brief Получить точечный источник освещения по имени.
     * @param name имя источника освещения.
     * @return источник освещения с заданным именем.
     * @note в случае невозможности создать источник освещения с заданными параметрами возвращает nullptr.
     */
    CPointLight *getPointLight(const std::string &name) const;

    /**
     * @brief Получить направленный источник освещения по имени.
     * @param name имя источника освещения.
     * @return источник освещения с заданным именем.
     * @note в случае невозможности создать источник освещения с заданными параметрами возвращает nullptr.
     */
    CDirectionLight *getDirectionLight(const std::string &name) const;

    /**
     * @brief Создать источник освещения.
     * @param name имя камеры.
     * @param type тип камеры.
     */
    void makeLight(const std::string &name, ELightType type);

private:
    CLightFactory();
    ~CLightFactory();
    CLightFactory(const CLightFactory &);
    CLightFactory &operator=(const CLightFactory &);

    static CLightFactory *instance;
    std::map<std::pair<std::string, ELightType>, AbstractLight*> lights;
}; // class CLightFactory

} // namespace core

#endif // LIGHTFACTORY_H
