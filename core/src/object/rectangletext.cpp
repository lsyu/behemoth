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

#include "rectangletext.h"
#include "rectanglesymbol.h"
#include "core/ogl/ogl.h"
#include "core/factory/texturefactory.h"
#include "core/factory/fontfactory.h"
#include "core/factory/shaderfactory.h"
#include "core/application.h"

namespace core {

CRectangleText::CRectangleText() : CRectangle(), font(new CFont("UNKNOWN", 14)), lines(),
        fontHeight(0.5f)
{
    lines.push_back(std::vector<CRectangleSymbol*>());
}

CRectangleText::~CRectangleText()
{
    delete font;
}

void CRectangleText::configure()
{
    this->font->setHeight(fontHeight/* * 0.5f * (float)CApplication::getInstance()->getSize().y*/);
    parent = this->parent;
    x = parent->getXMin();
    y = parent->getYMin();
    width = parent->getXMax() - parent->getXMin();
    height = parent->getYMax() - parent->getYMin();
    for (char c: text) {
        addSymbol(c);
    }
    int curLine = -1;
    float x = 0.0f, y = 0.0f;
    for (AbstractEntity *i: getChilds()) {
        CRectangleSymbol *s = dynamic_cast<CRectangleSymbol*>(i);
        // Каждую линию теста - в соответствии с выравниваем
        if (curLine == -1) {
            if (font->getVerticalAlign() == EVerticalAlign::Bottom)
                y = (lines.front().front()->getYMax() - lines.back().front()->getYMin() - height);
            else if (font->getVerticalAlign() == EVerticalAlign::Center)
                y = 0.5 * (lines.front().front()->getYMax() - lines.back().front()->getYMin() - height);
            else if (font->getVerticalAlign() == EVerticalAlign::Top); // ничего не делаем
        }
        if (curLine != s->lineNumber) {
            if (font->getHorizontalAlign() == EHorizontalAlign::Left); // ничего не делаем
            else if (font->getHorizontalAlign() == EHorizontalAlign::Center)
                x = -0.5 * (lines[s->lineNumber].back()->getXMax() - lines[s->lineNumber].front()->getXMin() - width);
            else if (font->getHorizontalAlign() == EHorizontalAlign::Right)
                x = -(lines[s->lineNumber].back()->getXMax() - lines[s->lineNumber].front()->getXMin() - width);
            curLine = s->lineNumber;
        }
        s->translate(glm::vec2(x, y));
        s->configure();
    }
}

void CRectangleText::paint() const
{
    for (int i = vChilds.size()-1; i >= 0; --i)
        vChilds[i]->paint();
}

void CRectangleText::setFont(const CFont &font)
{
    this->font = new CFont(font);
}

void CRectangleText::setFont(const std::string &name)
{
    this->font->setName(name);
}

void CRectangleText::setFont(float height)
{
    this->fontHeight = height;

    if (fontHeight > 1.0f)
        fontHeight -= (int)fontHeight;
    // TODO: подумать, на что домножать, когда межстрочный интервал появится!
    fontHeight *= (2.0f/3.0f) * 2.0f;
}

void CRectangleText::setFontQuantity(int quantity)
{
    this->font->setQuantity(quantity);
}

void CRectangleText::setFontAlign(EVerticalAlign vAlign)
{
    this->font->setVericalAlign(vAlign);
}

void CRectangleText::setFontAlign(EHorizontalAlign hAlign)
{
    this->font->setHorizontalAlign(hAlign);
}

void CRectangleText::setText(const std::string &text)
{
    this->text = text;
}

void CRectangleText::addSymbol(char symbol)
{
    CRectangleSymbol *s = new CRectangleSymbol(symbol, font, width, height, fontHeight, this);
    s->prepare();
}

} // namespace core
