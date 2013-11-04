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

#include <ft2build.h>
#include <freetype/freetype.h>

#include <map>
#include <vector>
#include <list>
#include <string>

#include <glm/glm.h>

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
     * @brief Получить буфер для формирования изображения, содержащего текст text высотой fontHeight.
     * @param text текст для вывода.
     * @param color цвет текста.
     * @param ontHeight высота текста.
     * @param windowSize размеры экрана.
     */
    std::vector<glm::vec4> getTextBuffer(const std::string &text, const glm::vec3 &color,
            int fontHeight, const glm::ivec2 &windowSize);

private:
    CFontFactory();
    ~CFontFactory();
    CFontFactory(const CFontFactory&);
    CFontFactory &operator=(const CFontFactory&);

    struct Symbol {
        unsigned short int width;
        unsigned short int height;
        std::list<glm::vec4> symbol;
    }; // struct Symbol

    /**
     * @brief Получить символ c.
     * @param c символ.
     * @param height высота шрифта.
     */
    Symbol getSymbol(char c, int height);

    static CFontFactory *instance;
    FT_Library library;
    FT_Face face;
    std::map<char, Symbol > symbols;
}; // class CFontFactory

} // namespace core

#endif // FONTFACTORY_H
