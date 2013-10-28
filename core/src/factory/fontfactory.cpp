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

#include "fontfactory.h"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>

using std::string;
using std::cout;


namespace core {

CFontFactory *CFontFactory::instance = nullptr;

class __CFontFactoryImplDel {
public:
    explicit __CFontFactoryImplDel(CFontFactory *fontFactory) : fontFactory(fontFactory) {}
    ~__CFontFactoryImplDel() {delete fontFactory;}
private:
    CFontFactory *fontFactory;
};

CFontFactory *CFontFactory::getInstance()
{
    if (!instance) {
        instance = new CFontFactory();
        static __CFontFactoryImplDel delHelper(instance);
    }
    return instance;
}

CFontFactory::CFontFactory()
{
    FT_Error error = FT_Init_FreeType(&library);
    if (error) {
        // TODO: Подумать над обработкой!
        cout << "ololo\n";
    }
    // TODO: Получать из ресурсов!
    // TODO: Подумать, как получить нативный путь
    error = FT_New_Face(library, "/home/lsyu/workspace/gui-build/DejaVuSans.ttf", 0, &face);
    if (error) {
        // TODO: Подумать над обработкой!
        cout << "ololo\n";
    }
}

CFontFactory::~CFontFactory()
{
    FT_Done_Face(face);
    FT_Done_FreeType(library);

}

std::list<glm::vec4> CFontFactory::getSymbol(char c)
{
    std::map<char, std::list<glm::vec4> >::iterator symbol
            = symbols.find(c);
    if (symbol != symbols.end())
        return symbol->second;

    // TODO: Обработка ошибок!
    FT_Load_Char(face, c, FT_LOAD_RENDER);

    FT_GlyphSlot g = face->glyph;
    std::list<glm::vec4> ret(g->bitmap.rows*g->bitmap.width);

    for (int y = 0, n = g->bitmap.rows; y < n; y++)
    {
      for (int w = 0, n = g->bitmap.width; w < n; w++)
      {
        unsigned char c = g->bitmap.buffer[y * g->bitmap.width + w];
        ret.push_back( glm::vec4(c, c, c, c) );
      }
    }
    symbols[c] = ret;
    return ret;
}

std::vector<glm::vec4> CFontFactory::getTextBuffer(const std::string &text, const glm::vec3 &color,
        int fontHeight, const glm::ivec2 &windowSize)
{
    FT_Set_Char_Size( face, /* handle to face object */
                              0, /* char_width in 1/64th of points */
                              16*64, /* char_height in 1/64th of points */
                              windowSize.x, /* horizontal device resolution */
                              windowSize.y ); /* vertical device resolution */

    FT_Set_Pixel_Sizes( face, /* handle to face object */
                                0, /* pixel_width */
                                fontHeight ); /* pixel_height */

    std::list<glm::vec4> ret;
    int n = 0; // номер символа в тексте.
    for (char c: text) {
        std::list<glm::vec4> symbol = getSymbol(c);
        for (int i = 0, n = face->glyph->bitmap.rows; i < n; ++i) {
            std::list<glm::vec4>::iterator it = symbol.begin();
            it = std::next(it, n * face->glyph->bitmap.width);
            ret.insert(std::next(ret.begin(), n * face->glyph->bitmap.width), it, std::next(it, n * face->glyph->bitmap.width));
        }
        n++;
    }
    return std::vector<glm::vec4>( std::make_move_iterator(std::begin(ret)),
                std::make_move_iterator(std::end(ret)) );
}

} // namespace core
