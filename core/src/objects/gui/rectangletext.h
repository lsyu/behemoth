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

#ifndef RECTANGLETEXT_H
#define RECTANGLETEXT_H

#include "basic2dentity.h"
#include "core/fonts/font.h"
#include <vector>
#include <set>

namespace core {

class CRectangleSymbol;

/**
 * @brief Область текста.
 *
 * Текст составляется из объектов CRectangleSymbol.
 * @n
 *
 */
class CRectangleText : public CBasic2dEntity
{
public:
    friend class CRectangleSymbol;

    CRectangleText();
    virtual ~CRectangleText();

    virtual void paint() const override;
    virtual void onClicked(const CEventMouseClick &event) override;

    virtual void setColor(const glm::vec3 &/*color*/) {}
    virtual float getXMin() const override {return x;}
    virtual float getXMax() const override {return x+width;}
    virtual float getYMin() const override {return y;}
    virtual float getYMax() const override {return y+height;}

    /**
     * @brief Установить цвет шрифта для отображения.
     * @note в соответствии с установленым шрифтом м текстом сгенерируется буферизображения шрифта.
     */
    void setFont(const CFont &font);
    void setFont(const std::string &name);
    std::string getFontName() const;
    void setFont(float height);
    float getFontHeight() const;
    void setFontQuantity(int quantity);
    void setFontAlign(core::EVerticalAlign vAlign);
    EVerticalAlign getVerticalAlign() const;
    void setVerticalAlign(const std::string &vAlign);
    std::string getVericalAlignStr() const;
    void setFontAlign(core::EHorizontalAlign hAlign);
    EHorizontalAlign getHorizontalAlign() const;
    void setHorizontalAlign(const std::string &hAlign);
    std::string getHorizontalAlignStr() const;
    /**
     * @brief Установить текст.
     * @note в соответствии с установленым шрифтом м текстом сгенерируется буфер изображения шрифта.
     */
    void setText(const std::string &text);
    std::string getText() const;

protected:
    virtual void configure() override;

private:
    /**
     * @brief Добавить символ.
     */
    void addSymbol(char symbol);

    CFont font;
    std::vector< std::vector<CRectangleSymbol*> > lines;
    std::multiset<CRectangleSymbol*> symbols;
    float fontHeight;
    std::string text;
    float x;
    float y;
    float width;
    float height;
}; // class CRectangleFont

} // namespace core

#endif // RECTANGLETEXT_H
