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

#ifndef RECTANGLEFONT_H
#define RECTANGLEFONT_H

#include "rectangle.h"
#include "font.h"
#include "textbuffer.h"

namespace core {

/**
 * @brief The CRectangleFont class
 */
class CRectangleFont : public CRectangle
{
public:
    CRectangleFont();
    virtual ~CRectangleFont();

    /**
     * @brief Установить цвет шрифта для отображения.
     * @note в соответствии с установленым шрифтом м текстом сгенерируется буферизображения шрифта.
     */
    void setFont(const CFont &font);
    void setFont(const std::string &name);
    void setFont(float height);
    void setFontQuantity(int quantity);
    void setFontAlign(core::EVerticalAlign vAlign);
    void setFontAlign(core::EHorizontalAlign hAlign);
    /**
     * @brief Установить текст.
     * @note в соответствии с установленым шрифтом м текстом сгенерируется буферизображения шрифта.
     */
    void setText(const std::string &text);

protected:
    virtual void configure();

private:
    CFont font;
    float fontHeight;
    std::string text;
    CTextBuffer buffer;
}; // class CRectangleFont

} // namespace core

#endif // RECTANGLEFONT_H
