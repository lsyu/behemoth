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

namespace core {

class AbstractEntity;
class Basic2dEntity;
class __CLuaManagerImplDel;

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
class CLuaManager
{
public:
    friend class __CLuaManagerImplDel; /**< Даже не думайте его использовать:) */
    /**
     * @brief Получить экземпляр менеджера работы с Lua.
     */
    static CLuaManager *getInstance();

    /**
     * @brief Прочитать файл описания интерфейса @a file.
     *
     * После парсинга скрипта луа наши декларативно описанные элементы
     * сохраняются в вектор, получить доступ к которым можно, воспользовавшись
     * методами @sa getObject, getObjects
     * @return true если скрипт выполнен, false в противном случае.
     */
    bool readGui(const std::string &file);

    /**
     * @brief Прочитать файл конфигурации.
     * @param file название файла конфигурации.
     * @return true, если файл конфигурации корректен и данные успешно прочитаны, false иначе.
     */
    bool readConfFile(const std::string &file);

    AbstractEntity *getObject(const std::string &id);
    AbstractEntity *getObject(int num);
    Basic2dEntity *getRootObject();
    const std::vector< std::shared_ptr<AbstractEntity> >& getObjects() const;

    template<class T>
    void addObject(AbstractEntity *entity);

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
     * @brief Регистрация текста.
     */
    void registerText();

    /**
     * @brief Регистрация таблицы conf.
     */
    void registerConf();
    /**
     * @brief регистрация методов для загрузки пути до файлов ресурсов.
     */
    void registerFolders();

private:
    CLuaManager();
    ~CLuaManager();
    CLuaManager(const CLuaManager &);
    CLuaManager &operator=(const CLuaManager&);

    bool parseFile(const std::string &fileName, CurrentTask task = TaskGUI);

    static CLuaManager *instance;
    lua_State *lua;
    std::vector< std::shared_ptr<core::AbstractEntity> > objects; /**< Элементы сцены.(Пока только GUI) */
    std::map<std::string, std::string> config; /**< Значения настроек конф. файлов. */
};

} // namespace Core

#endif // LUAMANAGER_H
