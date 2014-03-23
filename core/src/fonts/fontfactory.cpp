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

using std::string;


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

CFontFactory::Symbol CFontFactory::getSymbol(char c, const CFont &font)
{
    std::map<char, Symbol>::iterator symbol
            = m_symbols.find(c);
    if (symbol != m_symbols.end())
        return symbol->second;

    // TODO: Обработка ошибок!
    FT_Load_Char(m_face, c, FT_LOAD_RENDER);
    FT_GlyphSlot g = m_face->glyph;
    Symbol ret;
    ret.width = g->advance.x >> 6;
    ret.height = CFont::getQuantity();
    // забиваем по высоте
    for (int dx = 0, h = ret.height - g->bitmap_top; dx < ret.width; ++dx)
        for (int i = 0; i < h; ++i)
            ret.symbol.insert(ret.symbol.end(), {0, 0, 0, 0});

    // Рисуем основную часть буквы
    for (int y = 0, n = g->bitmap_top; y < n; ++y) {
        for (int x = 0, n = g->bitmap.pitch; x < n; ++x) {
            unsigned char c = g->bitmap.buffer[y * g->bitmap.pitch + x];
            ret.symbol.insert(ret.symbol.end(), {static_cast<unsigned char>(font.getColor().r),
                                                 static_cast<unsigned char>(font.getColor().g),
                                                 static_cast<unsigned char>(font.getColor().b),
                                                 c});
        }
        // добиваем по x пустыми символами
        for (int x = 0, n = ret.width - g->bitmap.pitch; x < n; ++x)
            ret.symbol.insert(ret.symbol.end(), {0, 0, 0, 0});
    }

    // Отступ - пока что пол размера шрифта
    // TODO: Сделать параметр настраеваемым!

    // рисуем то, что снизу
    for (int y = g->bitmap_top, n = g->bitmap.rows; y < n; ++y) {
        for (int x = 0, n = g->bitmap.pitch; x < n; ++x) {
            unsigned char c = g->bitmap.buffer[y * g->bitmap.pitch + x];
            ret.symbol.insert(ret.symbol.end(), {static_cast<unsigned char>(font.getColor().r),
                                                 static_cast<unsigned char>(font.getColor().g),
                                                 static_cast<unsigned char>(font.getColor().b),
                                                 c});
        }
        // добиваем по x
        for (int x = 0, n = ret.width - g->bitmap.pitch; x < n; ++x)
            ret.symbol.insert(ret.symbol.end(), {0, 0, 0, 0});
    }
    // Добиваем отступ
    for (int dx = 0, h = ret.height / 2.0f - (g->bitmap.rows - g->bitmap_top); dx < ret.width; ++dx)
        for (int i = 0; i < h; ++i)
            ret.symbol.insert(ret.symbol.end(), {0, 0, 0, 0});


    ret.height += ret.height * 0.5;

    m_symbols[c] = ret;
    return ret;
}

CTextBuffer CFontFactory::getTextBuffer(const std::string &text, const CFont &font,
                                        int parentWidth, int parentHeight)
{
    if (m_currentFont != font.getName()) {
        FT_New_Face(m_library, (CResourceManager::getInstance()->getFontFolder()
                + CResourceManager::getInstance()->getFileSeparator()
                + font.getName() + std::string(".ttf")).c_str(),
                0, &m_face);
    }

    FT_Set_Char_Size( m_face, /* handle to face object */
            0, /* char_width in 1/64th of points */
            16*64, /* char_height in 1/64th of points */
            parentWidth, /* horizontal device resolution */
            parentHeight); /* vertical device resolution */

    FT_Set_Pixel_Sizes( m_face, /* handle to face object */
            0, /* pixel_width */
            font.getHeight()); /* pixel_height */

    std::list<unsigned char> retBuf;
    int wTotal = 0;
    for (char c: text) {
        Symbol symbol = getSymbol(c, font);

        int w = symbol.width;
        wTotal += w;

        for (int y = 0, m = symbol.height; y < m; ++y) {
            std::list<unsigned char>::iterator pos = std::next(retBuf.begin(), 4 * (y*wTotal + wTotal - w));
            std::list<unsigned char>::iterator it = std::next(symbol.symbol.begin(), 4*y*w);
            std::list<unsigned char>::iterator it1 = std::next(it, 4*w);
            retBuf.insert(pos, it, it1);
        }
    }

    int retHeight = font.getHeight();
    int retWidth = wTotal;

    if (m_currentFont != font.getName()) {
        FT_Done_Face(m_face);
        m_currentFont = font.getName();
    }

    CTextBuffer ret;
    ret.buffer.reserve(retBuf.size());
    ret.buffer = std::vector<unsigned char>(std::make_move_iterator(std::begin(retBuf)),
            std::make_move_iterator(std::end(retBuf)));
    ret.width = retWidth;
    ret.height = retHeight;
    ret.isLoad = true;

    return ret;
}

CTextBuffer CFontFactory::getTextBuffer(char symbol, const CFont &font)
{
    bool inithere = false;
    if (m_currentFont != font.getName()) {
        FT_New_Face(m_library, (CResourceManager::getInstance()->getFontFolder()
                + CResourceManager::getInstance()->getFileSeparator()
                + font.getName() + std::string(".ttf")).c_str(),
                0, &m_face);
        inithere = true;
    }
    glm::ivec2 size = CApplication::getInstance()->getSize();
    FT_Set_Char_Size( m_face, /* handle to face object */
            0, /* char_width in 1/64th of points */
            16*64, /* char_height in 1/64th of points */
            size.x, /* horizontal device resolution */
            size.y); /* vertical device resolution */

    FT_Set_Pixel_Sizes( m_face, /* handle to face object */
            0, /* pixel_width */
            CFont::getQuantity()); /* pixel_height */

    Symbol s = getSymbol(symbol, font);

    if (m_currentFont != font.getName() && !inithere) {
        FT_Done_Face(m_face);
        m_currentFont = font.getName();
    }

    CTextBuffer ret;
    ret.buffer.reserve(s.symbol.size());
    ret.buffer = std::vector<unsigned char>(std::make_move_iterator(std::begin(s.symbol)),
            std::make_move_iterator(std::end(s.symbol)));
    ret.width = s.width;
    ret.height = s.height;
    ret.isLoad = true;

    return ret;
}

} // namespace behemoth
