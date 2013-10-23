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

#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <string>
#include <vector>

#include "glm/glm.h"

/**
 * @brief Содержит классы, структуры и перечисления, необходимые для функционирования графики.
 */
namespace core {

class CLuaManager;

/**
 * @brief Абстрактная сущность объекта сцены.
 */
class AbstractEntity
{
public:

    friend class CLuaManager;

    AbstractEntity() {}
    explicit AbstractEntity(const std::string &id) {}
    virtual ~AbstractEntity() {}

    /**
     * @brief Нарисовать сущность.
     */
    virtual void paint() const = 0;
    /**
     * @brief Установить цвет.
     */
    virtual void setColor(const glm::vec3 &color) = 0;

    /**
     * @brief Получить минимальную абсциссу ограничивающей поверхности.
     */
    virtual float getXMin() const = 0;
    /**
     * @brief Получить максимальную абсциссу ограничивающей поверхности.
     */
    virtual float getXMax() const = 0;
    /**
     * @brief Получить минимальную оординату ограничивающей поверхности.
     */
    virtual float getYMin() const = 0;
    /**
     * @brief Получить максимальную оординату ограничивающей поверхности.
     */
    virtual float getYMax() const = 0;

    /**
     * @brief Вернуть идентификатор сущности.
     */
    virtual std::string getId() const = 0;

    /**
     * @brief Установить родителя.
     */
    virtual void setParent(AbstractEntity *parent) = 0;

    /**
     * @brief Получить родителя сущности.
     */
    virtual AbstractEntity* getParent() const = 0;
    /**
     * @brief isRoot Является элемент корневым.
     */
    virtual bool isRoot() const = 0;

    /**
     * @brief Добавить ребенка сущности.
     */
    virtual void addChild(AbstractEntity *child) = 0;

    /**
     * @brief getChild Получить ребенка сущности по его имени.
     * @note В случае, если ребенка с именем id не найдено, вернется nullptr.
     */
    virtual AbstractEntity* getChild(const std::string &id) = 0;
    /**
     * @brief getChilds Получить вектор детей сущности.
     */
    virtual const std::vector<AbstractEntity*>& getChilds() const = 0;

protected:

    /**
     * @brief Конфигурирование сущности после загрузки данных.
     */
    virtual void configure() = 0;
}; // class AbstractEntity

} // namespace Core

#endif // ABSTRACTENTITY_H
