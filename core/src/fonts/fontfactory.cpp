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

#include "fontfactory.h"
#include "core/lua/resourcemanager.h"
#include "core/application/application.h"

#include <iostream>

namespace behemoth {

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

CFontFactory::CFontFactory() : m_symbols(), m_currentFont()
{
    FT_Error error = FT_Init_FreeType(&m_library);
    if (error) {
        // TODO: Подумать над обработкой!
    }
}

CFontFactory::~CFontFactory()
{
    FT_Done_FreeType(m_library);
}

CFontFactory::Symbol *CFontFactory::getSymbol(char c, const CFont &font)
{
    CFontInstance key = {c, font};
    CSymbols::iterator symbol = m_symbols.find(key);
    if (symbol != m_symbols.end())
        return symbol->second;

    FT_GlyphSlot g = m_face->glyph;
    Symbol *ret = new Symbol;

    // TODO: Обработка ошибок!
    FT_Load_Char(m_face, c, FT_LOAD_RENDER);

    int height = (m_face->size->metrics.ascender - m_face->size->metrics.descender) >> 6;
    if (c == ' ') {
        ret->symbol.insert(ret->symbol.end(), height * height/2 * 4, 0);
        ret->height = height;
        ret->width = height/2;
        return ret;
    }

    int advanceX =(g->metrics.width >>6) +1.0/10.0*height; // TODO: смещение м/ду символами.
    int advanceY = g->metrics.vertAdvance >> 6;
    int bearningY = advanceY - g->bitmap_top;


    // забиваем по высоте
    ret->symbol.insert(ret->symbol.end(), bearningY * advanceX * 4, 0);
    // Рисуем основную часть буквы
    for (int y = 0, n = g->bitmap.rows; y < n; ++y) {
        for (int x = 0, m = g->bitmap.width; x < m; ++x) {
            ret->symbol.insert(ret->symbol.end(), {static_cast<unsigned char>(font.getColor().r),
                                                 static_cast<unsigned char>(font.getColor().g),
                                                 static_cast<unsigned char>(font.getColor().b),
                                                 g->bitmap.buffer[y * m + x]});
        }
        ret->symbol.insert(ret->symbol.end(), (advanceX - g->bitmap.width)*4, 0);
    }
    int correct = (height - g->bitmap.rows - bearningY)*advanceX*4;
    if (correct > 0) // если есть место, добиваем
            ret->symbol.insert(ret->symbol.end(), correct, 0);
    else if (correct < 0) // если нет, удаляем.
        ret->symbol.erase(ret->symbol.begin(), std::next(ret->symbol.begin(), -correct));

    ret->width = advanceX;
    ret->height = height;
    m_symbols.insert(std::make_pair(key,ret));
    return ret;
}

//CTextureBuffer *CFontFactory::getTextBuffer(const std::string &text, const CFont &font,
//                                        int parentWidth, int parentHeight)
//{
//    static bool isInit = false;
//    if (m_currentFont != font.getName()) {
//        if (isInit) {
//            FT_Done_Face(m_face);
//        }
//        FT_New_Face(m_library, (CResourceManager::getInstance()->getFontFolder() + font.getName() + ".ttf").c_str(), 0, &m_face);
//        m_currentFont = font.getName();
//        isInit = true;
//    }

//    glm::ivec2 size = CApplication::getInstance()->getSize();
//    int font_h = font.getHeight()*size.y;
//    FT_Set_Char_Size( m_face, /* handle to face object */
//            font_h>>6, /* char_width in 1/64th of points */
//            font_h>>6, /* char_height in 1/64th of points */
//            parentWidth, /* horizontal device resolution */
//            parentHeight); /* vertical device resolution */

//    FT_Set_Pixel_Sizes( m_face, /* handle to face object */
//            0, /* pixel_width */
//            font.getHeight()); /* pixel_height */

//    std::list<unsigned char> retBuf;
//    int wTotal = 0;
//    for (char c: text) {
//        Symbol *symbol = getSymbol(c, font);

//        int w = symbol->width;
//        wTotal += w;

//        for (int y = 0, m = symbol->height; y < m; ++y) {
//            std::list<unsigned char>::iterator pos = std::next(retBuf.begin(), 4 * (y*wTotal + wTotal - w));
//            std::list<unsigned char>::iterator it = std::next(symbol->symbol.begin(), 4*y*w);
//            std::list<unsigned char>::iterator it1 = std::next(it, 4*w);
//            retBuf.insert(pos, it, it1);
//        }
//    }

//    int retHeight = font.getHeight();
//    int retWidth = wTotal;

//    CTextureBuffer *ret = new CTextureBuffer;
//    ret->m_buffer.reserve(retBuf.size());
//    ret->m_buffer = std::vector<unsigned char>(std::make_move_iterator(std::begin(retBuf)),
//            std::make_move_iterator(std::end(retBuf)));
//    ret->m_width = retWidth;
//    ret->m_height = retHeight;

//    return ret;
//}

CTextureBuffer *CFontFactory::getTextBuffer(char symbol, const CFont &font)
{
    static bool isInit = false;
    if (m_currentFont != font.getName()) {
        if (isInit) {
            FT_Done_Face(m_face);
        }
        FT_New_Face(m_library, (CResourceManager::getInstance()->getFontFolder() + font.getName() + ".ttf").c_str(), 0, &m_face);
        m_currentFont = font.getName();
        isInit = true;
    }
    glm::ivec2 size = CApplication::getInstance()->getSize();
    int font_h = font.getHeight()*size.y;
    FT_Set_Char_Size( m_face, /* handle to face object */
            font_h<<6, /* char_width in 1/64th of points */
            font_h<<6, /* char_height in 1/64th of points */
            size.x, /* horizontal device resolution */
            size.y); /* vertical device resolution */

    FT_Set_Pixel_Sizes( m_face, /* handle to face object */
            0, /* pixel_width */
            font_h); /* pixel_height */

    Symbol *s = getSymbol(symbol, font);
    CTextureBuffer *ret = new CTextureBuffer;
    ret->m_buffer.reserve(s->height*s->width);
    ret->m_buffer = std::vector<unsigned char>(std::make_move_iterator(std::begin(s->symbol)),
            std::make_move_iterator(std::end(s->symbol)));
    ret->m_width = s->width;
    ret->m_height = s->height;
//    delete s;

    return ret;
}

} // namespace behemoth
