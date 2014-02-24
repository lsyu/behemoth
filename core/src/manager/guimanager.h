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

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "lua/lua.h"

namespace core {

class AbstractEntity;
class Basic2dEntity;
class __CGUIManagerImplDel;

/**
 * @brief Менеджер работы с Lua.
 *
 * Архитектура - singleton. @n
 * Позволяет декларативно описывать данные, используя язык Lua. @n
 *
 * На данный момент есть возможность загрузки элементов графического пользовательского интерфейса,
 * а также загрузка путей ресурсов. @n
 * Элементы GUI:
 * - glm::vec2 (конструктор)
 * - glm::vec3 (конструктор)
 * - Rectangle
 * - Text - в разработке!
 *
 */
class CGUIManager
{
public:
    friend class __CGUIManagerImplDel; /**< Даже не думайте его использовать:) */
    /**
     * @brief Получить экземпляр менеджера работы с Lua.
     */
    static CGUIManager *getInstance();

    /**
     * @brief Прочитать файл описания интерфейса с именем @a fileName.
     *
     * После парсинга скрипта луа наши декларативно описанные элементы
     * сохраняются в вектор, получить доступ к которым можно, воспользовавшись
     * методами @sa getObject, getObjects
     * @return true если скрипт выполнен, false в противном случае.
     */
    bool readGui(const std::string &fileName);

    AbstractEntity *getObject(const std::string &id);
    AbstractEntity *getObject(int num);
    Basic2dEntity *getRootObject();
    const std::vector< std::shared_ptr<AbstractEntity> >& getObjects() const;

    template<class T>
    void addObject(AbstractEntity *entity);

    /**
     * @brief Выполнить onClick из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    bool runOnClickFor(AbstractEntity *entity);

protected:
    /**
     * @brief Инициализация и регистрирование всех доп. возможностей.
     */
    void init();
    /**
     * @brief Закрытие.
     */
    void close();
    /**
     * @brief Регистрация таблицы ui
     */
    void registerUI();
    /**
     * @brief Регистрация glm::vec2
     */
    void registerVec2();
    /**
     * @brief Регистрация glm::vec3
     */
    void registerVec3();
    /**
     * @brief регистрация core::Border
     */
    void registerBorder();
    /**
     * @brief Регистрация core::Rectangle.
     */
    void registerRectangle();
    /**
     * @brief Регистрация core::RectangleText.
     */
    void registerText();

private:
    CGUIManager();
    ~CGUIManager();
    CGUIManager(const CGUIManager &);
    CGUIManager &operator=(const CGUIManager&);

    static CGUIManager *instance;
    lua_State *lua;
    std::vector< std::shared_ptr<core::AbstractEntity> > objects; /**< Элементы сцены.(Пока только GUI) */
};

} // namespace Core

#endif // GUIMANAGER_H
