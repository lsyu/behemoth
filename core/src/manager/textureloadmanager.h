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

#ifndef TEXTURELOADMANAGER_H
#define TEXTURELOADMANAGER_H

#include <string>
#include <memory>
#include <map>

namespace Core {

class __TextureLoaderManagerImplDel;

/**
 * @brief Менеджер загрузки текстур.
 *
 * Архитектура - singleton.
 * Во время запуска программы загружает все текстуры.
 * Каждая текстура загружается один раз.
 */
class TextureLoadManager
{
public:
    friend class __TextureLoaderManagerImplDel;

    /**
     * @brief Получить экземпляр менеджера текстур.
     * @return экземпляр менеджера текстур.
     */
    static TextureLoadManager* getInstance();

    /**
   * @brief Загрузка текстуры с именем @a name из изображения @a textureName.
   *
   * Необходимо указывать только файл изображения. Предполагается, что он находится в директории
   * тектур (описывается в файле конфигурации).
   *
   * @param name имя текстуры.
   * @param textureName имя файла изображения.
   * @return  true если текстура удачно загружена, false в противном случае.
   */
    bool loadTexture(const std::string &name, const std::string &textureName);

    /**
   * @brief Получить текстуру по имени.
   * @param name название текстуры.
   * @return код текстуры. В случае, если текстура не загружена, возвращается 0.
   */
    uint getTexture(const std::string &name) const;

private:
    TextureLoadManager();
    ~TextureLoadManager();
    TextureLoadManager(const TextureLoadManager&);
    TextureLoadManager &operator=(const TextureLoadManager&);
    
    static TextureLoadManager *instance;
    std::map<std::string, uint> textures;
}; // class TextureLoadManager

} // namespace Core

#endif // TEXTURELOADMANAGER_H
