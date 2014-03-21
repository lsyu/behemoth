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
#include "core/ogl/texturefactory.h"
#include "core/ogl/shaderfactory.h"
#include "core/fonts/fontfactory.h"
#include "core/application/application.h"

#include "algorithm"

namespace core {

CRectangleText::CRectangleText() : CBasic2dEntity(), font("UNKNOWN", 14), lines(), symbols(),
    fontHeight(0.5f), x(-1.0f), y(-1.0f), width(2.0f), height(2.0f)
{
    lines.push_back(std::vector<CRectangleSymbol*>());
}

CRectangleText::~CRectangleText()
{
}

void CRectangleText::configure()
{
    this->font.setHeight(fontHeight);
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
            if (font.getVerticalAlign() == EVerticalAlign::Bottom)
                y = (lines.front().front()->getYMax() - lines.back().front()->getYMin() - height);
            else if (font.getVerticalAlign() == EVerticalAlign::Center)
                y = 0.5 * (lines.front().front()->getYMax() - lines.back().front()->getYMin() - height);
            else if (font.getVerticalAlign() == EVerticalAlign::Top); // ничего не делаем
        }
        if (curLine != s->lineNumber) {
            if (font.getHorizontalAlign() == EHorizontalAlign::Left); // ничего не делаем
            else if (font.getHorizontalAlign() == EHorizontalAlign::Center)
                x = -0.5 * (lines[s->lineNumber].back()->getXMax() - lines[s->lineNumber].front()->getXMin() - width);
            else if (font.getHorizontalAlign() == EHorizontalAlign::Right)
                x = -(lines[s->lineNumber].back()->getXMax() - lines[s->lineNumber].front()->getXMin() - width);
            curLine = s->lineNumber;
        }
        s->translate(glm::vec2(x, y));
        s->configure();
    }
}

void CRectangleText::paint() const
{
    CShader *shader = CShaderFactory::getInstance()->getShader("text");
    shader->setUniform("texture", 0);

    CRectangleSymbol *prev = nullptr;
    for (std::multiset<CRectangleSymbol*>::iterator it = symbols.cbegin(), end = symbols.cend();
         it != end; ++it) {
        if (!prev || prev->symbol != (*it)->symbol) {
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (*it)->texture.getId());
        }
        (*it)->paint();
        prev = *it;
    }
}

void CRectangleText::onClicked(const CEventMouseClick &/*event*/)
{
}

void CRectangleText::setFont(const CFont &font)
{
    this->font = font;
}

void CRectangleText::setFont(const std::string &name)
{
    this->font.setName(name);
}

std::string CRectangleText::getFontName() const
{
    return font.getName();
}

void CRectangleText::setFont(float height)
{
    this->fontHeight = height;

    if (fontHeight > 1.0f)
        fontHeight -= (int)fontHeight;
    // TODO: подумать, на что домножать, когда межстрочный интервал появится!
    fontHeight *= (2.0f/3.0f) * 2.0f;
}

float CRectangleText::getFontHeight() const
{
    return font.getHeight();
}

void CRectangleText::setFontQuantity(int quantity)
{
    this->font.setQuantity(quantity);
}

void CRectangleText::setFontAlign(EVerticalAlign vAlign)
{
    this->font.setVericalAlign(vAlign);
}

EVerticalAlign CRectangleText::getVerticalAlign() const
{
    return font.getVerticalAlign();
}

void CRectangleText::setVerticalAlign(const std::string &align)
{
    if (align == "center")
        setFontAlign(EVerticalAlign::Center);
    else if (align == "top")
        setFontAlign(EVerticalAlign::Top);
    else if (align == "bottom")
        setFontAlign(EVerticalAlign::Bottom);
    //else
    // TODO: Обработка ситуации неправильного ввода
}

std::string CRectangleText::getVericalAlignStr() const
{
    switch (getVerticalAlign()) {
    case EVerticalAlign::Center:
        return "center";
    case EVerticalAlign::Top:
        return "top";
    case EVerticalAlign::Bottom:
        return "bottom";
    default:
        return "undefined";
    }
}

void CRectangleText::setFontAlign(EHorizontalAlign hAlign)
{
    this->font.setHorizontalAlign(hAlign);
}

EHorizontalAlign CRectangleText::getHorizontalAlign() const
{
    return font.getHorizontalAlign();
}

void CRectangleText::setHorizontalAlign(const std::string &align)
{
    if (align == "center")
        setFontAlign(EHorizontalAlign::Center);
    else if (align == "left")
        setFontAlign(EHorizontalAlign::Left);
    else if (align == "right")
        setFontAlign(EHorizontalAlign::Right);
    //else
    // TODO: Обработка ситуации неправильного ввода
}

std::string CRectangleText::getHorizontalAlignStr() const
{
    switch (getHorizontalAlign()) {
    case EHorizontalAlign::Center:
        return "center";
    case EHorizontalAlign::Left:
        return "left";
    case EHorizontalAlign::Right:
        return "right";
    default:
        return "undefined";
    }
}

void CRectangleText::setText(const std::string &text)
{
    this->text = text;
}

std::string CRectangleText::getText() const
{
    return text;
}

void CRectangleText::addSymbol(char symbol)
{
    CRectangleSymbol *s = new CRectangleSymbol(symbol, &font, width, height, fontHeight, this);
    symbols.insert(s);
    s->prepare();
}

} // namespace core
