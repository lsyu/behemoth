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
#include "core/manager/resourcemanager.h"

#include "glm/gtc/type_ptr.hpp"

using std::string;


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
    }
    error = FT_New_Face(library,
            (CResourceManager::getInstance()->getFontFolder()
             + CResourceManager::getInstance()->getFileSeparator()
             + std::string("DejaVuSans.ttf")).c_str(),
            0, &face);
    if (error) {
        // TODO: Подумать над обработкой!
    }
}

CFontFactory::~CFontFactory()
{
    FT_Done_Face(face);
    FT_Done_FreeType(library);

}

CFontFactory::Symbol CFontFactory::getSymbol(char c, int height)
{
    std::map<char, Symbol>::iterator symbol
            = symbols.find(c);
    if (symbol != symbols.end())
        return symbol->second;

    // TODO: Обработка ошибок!
    FT_Load_Char(face, c, FT_LOAD_RENDER);
    FT_GlyphSlot g = face->glyph;
    Symbol ret;
    ret.width = g->advance.x >> 6;
    ret.height = height;
    // забиваем по высоте
    for (int dx = 0; dx < ret.width; ++dx)
        for (int i = 0, h = height - g->bitmap.rows; i < h; ++i)
            ret.symbol.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

    for (int y = 0, n = g->bitmap.rows; y < n; ++y) {
        for (int x = 0, n = g->bitmap.pitch; x < n; ++x) {
            unsigned char c = g->bitmap.buffer[y * g->bitmap.pitch + x];
            ret.symbol.push_back( glm::vec4(c, c, c, c) );
        }
        // добиваем по x
        for (int x = 0, n = ret.width - g->bitmap.pitch; x < n; ++x)
            ret.symbol.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
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
    int wTotal = 0;
    for (char c: text) {
        Symbol symbol = getSymbol(c, fontHeight);

        int w = symbol.width;
        wTotal += w;

        for (int y = 0, m = symbol.height; y < m; ++y) {
            std::list<glm::vec4>::iterator pos = std::next(ret.begin(), y*wTotal + wTotal - w);
            std::list<glm::vec4>::iterator it = std::next(symbol.symbol.begin(), y*w);
            std::list<glm::vec4>::iterator it1 = std::next(it, w);
            ret.insert(pos, it, it1);
        }
    }

    //! TODO: Под размеры области!
//    int sizeTotal = windowSize.x * windowSize.y;
//    int sizeText = ret.size();
//    int halfDif = (sizeTotal - sizeText) / 2;
//    for (int i = 0; i < halfDif; ++i) {
//        ret.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
//        ret.push_front(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
//    }

    return std::vector<glm::vec4>( std::make_move_iterator(std::begin(ret)),
                std::make_move_iterator(std::end(ret)) );
}

} // namespace core
