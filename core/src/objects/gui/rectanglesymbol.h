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

#ifndef RECTANGLESYMBOL_H
#define RECTANGLESYMBOL_H

#include "rectangle.h"

namespace core {

class CFont;
class CRectangleText;
struct CSymbolTexture;

class CRectangleSymbol : public CRectangle
{
public:
    friend class CRectangleText;

    CRectangleSymbol(char symbol, CFont *font, float parentWidth, float parentHeight, float fontHeight,
                     CRectangleText *parent);
    virtual ~CRectangleSymbol();

    virtual void paint() const override;
    virtual void onClicked(const CEventMouseClick &event) override;

    bool operator >(CRectangleSymbol *other) const;

protected:
    virtual void configure() override;
    void prepare();
    void translate(const glm::vec2 &translate);

private:
    CFont *font;
    CSymbolTexture *symbolTex;
    char symbol;
    float parentWidth;
    float parentHeight;
    float fontHeight;
    int lineNumber;
}; // class CRectangleSymbol

} // namespace core

#endif // RECTANGLESYMBOL_H
