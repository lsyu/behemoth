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

#ifndef RECTANGLESYMBOL_H
#define RECTANGLESYMBOL_H

#include "rectangle.h"

namespace bhm {

class CFont;
class CRectangleText;
struct CSymbolTexture;

/**
 * @brief Область буквы.
 *
 * Прямоугольник с текстурой генерируется при выполнении void CRectangleText::addSymbol(char symbol)
 */
class CRectangleSymbol : public CRectangle
{
public:
    friend class CRectangleText;

    CRectangleSymbol(char symbol, CFont *m_font, float m_parentWidth, float parentHeight, float m_fontHeight,
                     CRectangleText *m_parent);
    virtual ~CRectangleSymbol();

    virtual void paint() const override;
    virtual void onClicked(const CEventMouseClick &event) override;

    bool operator >(CRectangleSymbol *other) const;

protected:
    virtual void configure() override;
    void prepare();
    void translate(const glm::vec2 &translate);

private:
    CFont *m_font;      /**< Шрифт данного символа. */
    char m_symbol;      /**< Символ. */
    float m_parentWidth;/**< Длина текста. */
    float parentHeight; /**< Высота текста. */
    float m_fontHeight; /**< Высота шрифта. */
    int m_lineNumber;   /**< Номер линии текста, в которой располагается символ. */
}; // class CRectangleSymbol

} // namespace behemoth

#endif // RECTANGLESYMBOL_H
