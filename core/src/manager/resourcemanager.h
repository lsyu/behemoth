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

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <map>

namespace Core {

class __ResourceManagerImplDel;
class LuaManager;

/**
 * @brief Менеджер ресурсов.
 *
 * Архитектура - singleton. @n
 * Предоставляет интерфейс для чтения файла конфигурации и загрузки ресурсов.
 * Каждая строка файла конфигурации представляет собой пару вида ключ: значение.
 * Например, строка @n shader =  "shaders" @n
 * означает, что шейдерные программы необходимо искать по относительному пути shaders/
 * @note В файле конфигурации обязательно должны быть строки:
 * - mesh
 * - material
 * - shader
 * - texture
 * @note Пример файла конфигурации:
 * @code
 * conf:folders
 * {
 *   mesh = "mesh",
 *   material = "material",
 *   texture = "texture",
 *   shader = "shaders"
 * } -- configuration of path to the resources
 * @endcode
 * @note Файл конфигурации называется core.conf и находится в той же директории,
 * что и исполняемый файл!
 */
class ResourceManager
{
public:
    friend class __ResourceManagerImplDel; /**< Не вздумай использовать этот класс! */
    friend class LuaManager;

    /**
     * @brief Получить экземпляр менеджера ресурсов.
     * @note Инициализация ресурсов происходит при первом обращении к экземпляру менеджера ресурсов.
     * @return экземпляр менеджера ресурсов.
     */
    static ResourceManager* getInstance();

    /**
     * @return string относительный путь до папки с файлами геометрии.
     */
    std::string getMeshFolder() const;

    /**
     * @return string относительный путь до папки с файлами материалов.
     */
    std::string getMaterialFolder() const;

    /**
     * @return string относительный путь до папки с файлами шейдерных программ.
     */
    std::string getShaderFolder() const;

    /**
     * @return string относительный путь до папки с файлами текстур.
     */
    std::string getTextureFolder() const;

    /**
     * @return string разделитель.
     */
    std::string getFileSeparator() const;

private:
    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager&);
    ResourceManager &operator=(const ResourceManager&);

    std::map<std::string, std::string> mapOfParam;
    static ResourceManager *instance;
}; // class ResourceManager

} // namespace Core

#endif // RESOURCEMANAGER_H
