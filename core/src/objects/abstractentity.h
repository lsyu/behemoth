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

#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <string>
#include <vector>

#include "glm/glm.h"

/**
 * @brief Содержит классы, структуры и перечисления, необходимые для функционирования графики.
 */
namespace behemoth {

/**
 * @brief Абстрактная сущность объекта сцены.
 */
class AbstractEntity
{
public:
    /**
     * @brief Нарисовать сущность.
     */
    virtual void paint() const = 0;
    /**
     * @brief Вернуть идентификатор сущности.
     */
    virtual std::string getId() const = 0;
    /**
     * @brief Конфигурирование сущности после загрузки данных.
     */
    virtual void configure() = 0;

protected:
    AbstractEntity() {}
    virtual ~AbstractEntity() {}
}; // class AbstractEntity

} // namespace behemoth

#endif // ABSTRACTENTITY_H
