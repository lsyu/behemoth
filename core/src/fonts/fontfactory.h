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

#ifndef FONTFACTORY_H
#define FONTFACTORY_H

#include "core/fonts/font.h"
#include "core/objects/gui/textbuffer.h"

#include <ft2build.h>
#include <freetype/freetype.h>

#include <map>
#include <vector>
#include <list>
#include <string>

namespace core {

class __CFontFactoryImplDel;

/**
 * @brief Фабрика получения шрифтов.
 */
class CFontFactory
{
public:
    friend class __CFontFactoryImplDel;
    /**
     * @brief Получить экземпляр фабрики шрифтов.
     */
    static CFontFactory *getInstance();

    /**
     * @brief Получить буфер для формирования изображения, содержащего текст text.
     * @param text текст для вывода.
     * @param font требуемый шрифт.
     * @param parentWidth длина родителя(в пикселях).
     * @param parentHeight высота родителя(в пикселях).
     */
    CTextBuffer getTextBuffer(const std::string &text, const CFont &font, int parentWidth, int parentHeight);

    /**
     * @brief Получить буфер для формирования изображения, содержащего символ symbol.
     * @param symbol текст для вывода.
     * @param font требуемый шрифт.
     */
    CTextBuffer getTextBuffer(char symbol, const CFont &font);

private:
    CFontFactory();
    ~CFontFactory();
    CFontFactory(const CFontFactory&);
    CFontFactory &operator=(const CFontFactory&);

    struct Symbol {
        unsigned short int width;
        unsigned short int height;
        std::list<unsigned char> symbol;
    }; // struct Symbol

    /**
     * @brief Получить символ c.
     * @param c символ.
     * @param font шрифт.
     */
    Symbol getSymbol(char c, const CFont &font);

    static CFontFactory *instance;

    std::map<char, Symbol > symbols;
    std::string currentFont;

    FT_Library library;
    FT_Face face;
}; // class CFontFactory

} // namespace core

#endif // FONTFACTORY_H
