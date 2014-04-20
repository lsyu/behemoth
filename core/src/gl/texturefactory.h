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

#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "texture.h"

#include "glm/glm.h"

namespace bhm {

class CFont;

/**
 * @brief Фабрика загрузки текстур.
 *
 * Каждая текстура загружается один раз.
 * Для загрузки текстур используется библиотека GLI.
 * @note Текстуры должны храниться в формате *.dds
 */
class CTextureFactory
{
public:
    /**
     * @brief Получить экземпляр фабрики текстур.
     * @return экземпляр фабрики текстур.
     */
    static CTextureFactory* getInstance();

    /**
     * @brief Получить текстуру по имени.
     * @param name название текстуры без расширения, т.е. для "texture.dds" имя текстуры будет "texture".
     */
    CTexture *getTexture(const std::string &name);
    /**
     * @brief Получить текстуру по данным.
     * @param buffer буфер для генерирования текстуры.
     * @param deleteAfter - удалять ли буффер после генерирования текстуры.
     */
    CTexture *getTexture(CTextureBuffer *buffer, const std::string &textureName, bool deleteAfter = true);

    CTexture *getSymbol(char symbol, const CFont &font);
    CTexture *getText(const std::string &text, const CFont &font);

private:
    CTextureFactory();
    ~CTextureFactory();
    CTextureFactory(const CTextureFactory&);
    CTextureFactory &operator=(const CTextureFactory&);

    /**
     * @brief Загрузка текстуры с именем @a name из изображения @a textureName.
     *
     * Необходимо указывать только файл изображения(без пути). Предполагается, что он находится в директории
     * тектур (описывается в файле конфигурации).
     *
     * @param name имя текстуры.
     * @param textureName имя файла изображения.
     */
    CTexture *loadTexture(const std::string &name, const std::string &textureName);

    /**
     * @brief Загрузка текстуры символа @a symbol.
     */
    CTexture *loadSymbol(char symbol);

    //from http://www.g-truc.net/project-0024.html#menu
    CTexture *createTexture2D(const std::string &filename);

    static CTextureFactory *instance;
    std::map< std::string, CTexture* > m_textures;                        /**< Контейнер текстур, загруженных из файлов. */
     std::map<std::pair<char, CFont>, CTexture*> m_symbols; /**< Контейнер текстур, сгенерированных для символов. */

    friend class __CTextureFactoryImplDel;
}; // class TextureFactory

} // namespace behemoth

#endif // TEXTUREFACTORY_H
