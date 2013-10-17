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

#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "lua/lua.h"

namespace Core {

class Entity;
class __LuaManagerImplDel;

/**
 * @brief Менеджер работы с Lua.
 *
 * Архитектура - singleton.
 * Является оберткой над функциями Lua.
 *
 * На данный момент загружаются следующие объекты:
 * - glm::vec2 (конструктор)
 * - glm::vec3 (конструктор)
 * - Rectangle
 */
class LuaManager
{
public:
    friend class __LuaManagerImplDel; /**< Даже не думайте его использовать:) */
    /**
     * @brief Получить экземпляр менеджера работы с Lua.
     */
    static LuaManager *getInstance();

    /**
     * @brief Выполнить скрипт @a file.
     *
     * После парсинга скрипталуа наши декларативно описанные элементы
     * сохраняются в вектор, получить доступ к которым можно, воспользовавшись
     * методами @sa getObject, getObjects
     * @return true если скрипт выполнен, false в противном случае.
     */
    bool doFile(const std::string &file);

    /**
     * @brief Прочитать файл конфигурации.
     * @param file название файла конфигурации.
     * @return true, если файл конфигурации корректен и данные успешно прочитаны, false иначе.
     */
    bool readConfFile(const std::string &file);

    Entity *getObject(const std::string &id);
    Entity *getObject(int num);
    const std::vector< std::shared_ptr<Entity> >& getObjects() const;

    template<class T>
    void addObject(Entity *entity);

protected:
    /**
     * @brief Текущая задача скрипта.
     *
     * Необходим для корректной подготовки стека Lua для работы с нашими объектами
     */
    enum CurrentTask {
        TaskGUI = 0,
        TaskConfig
    }; // enum Init
    /**
     * @brief Закрытие.
     */
    void close(CurrentTask task);
    /**
     * @brief Инициализация и регистрирование всех доп. возможностей.
     */
    void init(CurrentTask task);
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
     * @brief Регистрация прямоугольника.
     */
    void registerRectangle();

    /**
     * @brief Регистрация таблицы conf.
     */
    void registerConf();
    /**
     * @brief регистрация методов для загрузки пути до файлов ресурсов.
     */
    void registerFolders();

private:
    LuaManager();
    ~LuaManager();
    LuaManager(const LuaManager &);
    LuaManager &operator=(const LuaManager&);

    bool parseFile(const std::string &fileName, CurrentTask task = TaskGUI);

    static LuaManager *instance;
    lua_State *lua;
    std::vector< std::shared_ptr<Core::Entity> > objects; /**< Элементы сцены.(Пока только GUI) */
    std::map<std::string, std::string> config; /**< Значения настроек конф. файлов. */
};

} // namespace Core

#endif // LUAMANAGER_H
