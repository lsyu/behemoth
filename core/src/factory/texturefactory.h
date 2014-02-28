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

#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "core/objects/textbuffer.h"

#include "glm/glm.h"

namespace core {

class CFont;

class __CTextureFactoryImplDel;

struct CSymbolTexture {
    float width;     /**< относительная длина текстуры */
    float height;    /**< относительная высота текстуры */
    uint texture;   /**< идентификатор текстуры */
};

/**
 * @brief Менеджер загрузки текстур.
 *
 * Архитектура - singleton. @n
 * Каждая текстура загружается один раз.
 * Для загрузки текстур используется библиотека GLI.
 * @note Текстуры должны храниться в формате *.dds
 */
class CTextureFactory
{
public:
    friend class __CTextureFactoryImplDel;

    /**
     * @brief Получить экземпляр менеджера текстур.
     * Во время первого обращения загружаются все изображения.
     * @return экземпляр менеджера текстур.
     */
    static CTextureFactory* getInstance();

    /**
     * @brief Получить текстуру по имени.
     * @param name название текстуры без расширения, т.е. для "texture.dds" имя текстуры будет "texture".
     * @return код текстуры. В случае, если текстура не загружена, возвращается 0.
     */
    uint getTexture(const std::string &name);
    /**
     * @brief Получить текстуру по данным.
     * @param buffer буфер для генерирования текстуры текста.
     * @return код текстуры. В случае, если текстура не загружена, возвращается 0.
     */
    uint getTexture(const CTextBuffer &buffer) const;

    CSymbolTexture getSymbol(char symbol, const CFont &font, float parentWidth, float parentHeight);

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
     * @return id текстуры в случае удачной загрузки, 0 в противном случае.
     */
    uint loadTexture(const std::string &name, const std::string &textureName);

    /**
     * @brief Загрузка текстуры символа @a symbol.
     * @return id текстуры в случае удачной загрузки, 0 в противном случае.
     */
    uint loadSymbol(char symbol);

    //from http://www.g-truc.net/project-0024.html#menu
    unsigned int createTexture2D(const std::string &filename);
    
    static CTextureFactory *instance;
    std::map<std::string, uint> textures;
    std::map<char, CSymbolTexture> symbols;
}; // class TextureFactory

} // namespace Core

#endif // TEXTUREFACTORY_H
