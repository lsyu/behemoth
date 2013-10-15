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

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

#include "glm/glm.h"

/**
 * @brief Содержит классы, структуры и перечисления, необходимые для функционирования графики.
 */
namespace Core {

class LuaManager;

struct Border {
    Border() : width(0), color(0.0f, 0.0f, 0.0f) {}
    Border(const Border &other) : width(other.width), color(other.color) {}

    float width;
    glm::vec3 color;
};

/**
 * @brief Предоставляет интерфейс загрузки сущности объекта.
 *
 * Сущность объекта - это
 * - координаты вершин;
 * - нормали вершин;
 * - текстурные координаты вершин;
 * - материал объекта.
 *
 * @sa Core::Material
 */
class Entity
{
public:

    friend class LuaManager;

    Entity();
    explicit Entity(const std::string &id);
    virtual ~Entity();

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
    std::string getId() const;

    /**
     * @brief Установить родителя.
     */
    void setParent(Entity *parent);
    /**
     * @brief Получить родителя сущности.
     */
    const Entity* getParent() const;
    /**
     * @brief Получить родителя сущности.
     */
    Entity* getParent();
    /**
     * @brief isRoot Является элемент корневым.
     */
    bool isRoot() const;

    /**
     * @brief Добавить ребенка сущности.
     */
    void addChild(Entity *child);
    /**
     * @brief getChild Получить ребенка сущности по его имени.
     * @note В случае, если ребенка с именем id не найдено, вернется nullptr.
     */
    const Entity* getChild(const std::string &id) const;
    /**
     * @brief getChild Получить ребенка сущности по его имени.
     * @note В случае, если ребенка с именем id не найдено, вернется nullptr.
     */
    Entity* getChild(const std::string &id);
    /**
     * @brief getChilds Получить вектор детей сущности.
     */
    const std::vector<Entity*>& getChilds() const;

protected:
//    /**
//     * @brief Загрузка геометрии.
//     * @param fileName файл геометрии.
//     * @return true в случае спеха, false иначе.
//     */
//    bool loadData(const std::string &fileName);

    /**
     * @brief Конфигурирование сущности после загрузки данных.
     */
    virtual void configure() = 0;

    std::vector<glm::vec2> vPos2;      /**< вектор координат */
    std::vector<glm::vec3> vPos3;      /**< вектор координат */
    std::vector<glm::vec3> vNormal;    /**< вектор нормалей */
    std::vector<glm::vec2> vUV;        /**< вектор текстурных координат */
    std::vector<glm::vec3> vColor;     /**< вектор цветов вершин */
    std::vector<Entity*> vChilds;      /**< вектор детей */
    Entity *parent;                    /**< родитель */
    bool root;
    // Material material; //! TODO: Подумать над материалом!

private:
    std::string id;
}; // class Entity

} // namespace Core

#endif // ENTITY_H
