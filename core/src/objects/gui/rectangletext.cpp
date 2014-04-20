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

#include "rectangletext.h"
#include "rectanglesymbol.h"
#include "core/ogl/ogl.h"
#include "core/ogl/texturefactory.h"
#include "core/ogl/shaderfactory.h"
#include "core/fonts/fontfactory.h"
#include "core/application/application.h"

#include "algorithm"

namespace bhm {

CRectangleText::CRectangleText() : CBasic2dEntity(), m_font("DejaVuSans", 14), m_vAlign(EVerticalAlign::center),
    m_hAlign(EHorizontalAlign::center), m_lines(), m_symbols(), m_fontHeight(0.5f), m_x(-1.0f), m_y(-1.0f),
    m_width(2.0f), m_height(2.0f)
{
    m_lines.push_back(std::vector<CRectangleSymbol*>());
}

CRectangleText::~CRectangleText()
{
}

void CRectangleText::configure()
{
    this->m_font.setHeight(m_fontHeight);
    m_parent = this->m_parent;
    m_x = m_parent->getXMin();
    m_y = m_parent->getYMin();
    m_width = m_parent->getXMax() - m_parent->getXMin();
    m_height = m_parent->getYMax() - m_parent->getYMin();
    for (char c: m_text) {
        addSymbol(c);
    }
    int curLine = -1;
    float x = 0.0f, y = 0.0f;
    for (AbstractEntity *i: getChilds()) {
        CRectangleSymbol *s = dynamic_cast<CRectangleSymbol*>(i);
        // Каждую линию теста - в соответствии с выравниваем
        if (curLine == -1) {
            if (m_vAlign == EVerticalAlign::bottom)
                y = (m_lines.front().front()->getYMax() - m_lines.back().front()->getYMin() - m_height);
            else if (m_vAlign == EVerticalAlign::center)
                y = 0.5 * (m_lines.front().front()->getYMax() - m_lines.back().front()->getYMin() - m_height);
            else if (m_vAlign == EVerticalAlign::top); // ничего не делаем
        }
        if (curLine != s->m_lineNumber) {
            if (m_hAlign == EHorizontalAlign::left); // ничего не делаем
            else if (m_hAlign == EHorizontalAlign::center)
                x = -0.5 * (m_lines[s->m_lineNumber].back()->getXMax() - m_lines[s->m_lineNumber].front()->getXMin() - m_width);
            else if (m_hAlign == EHorizontalAlign::right)
                x = -(m_lines[s->m_lineNumber].back()->getXMax() - m_lines[s->m_lineNumber].front()->getXMin() - m_width);
            curLine = s->m_lineNumber;
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
    for (std::multiset<CRectangleSymbol*>::iterator it = m_symbols.cbegin(), end = m_symbols.cend();
         it != end; ++it) {
        if (!prev || prev->m_symbol != (*it)->m_symbol) {
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (*it)->m_texture->getId());
            shader->setUniform("color", (*it)->m_font->getColor());
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
    this->m_font = font;
}

void CRectangleText::setFont(const std::string &name)
{
    this->m_font.setName(name);
}

std::string CRectangleText::getFontName() const
{
    return m_font.getName();
}

void CRectangleText::setFont(float height)
{
    this->m_fontHeight = height;

    if (m_fontHeight > 1.0f)
        m_fontHeight -= (int)m_fontHeight;
    // TODO: подумать, на что домножать, когда межстрочный интервал появится!
    m_fontHeight *= (2.0f/3.0f) * 2.0f;
}

float CRectangleText::getFontHeight() const
{
    return m_font.getHeight();
}

//void CRectangleText::setFontQuantity(int quantity)
//{
//    this->m_font.setQuantity(quantity);
//}

void CRectangleText::setFontAlign(EVerticalAlign vAlign)
{
    m_vAlign = vAlign;
}

EVerticalAlign CRectangleText::getVerticalAlign() const
{
    return m_vAlign;
}

void CRectangleText::setVerticalAlign(const std::string &align)
{
    if (align == "center")
        setFontAlign(EVerticalAlign::center);
    else if (align == "top")
        setFontAlign(EVerticalAlign::top);
    else if (align == "bottom")
        setFontAlign(EVerticalAlign::bottom);
    //else
    // TODO: Обработка ситуации неправильного ввода
}

std::string CRectangleText::getVericalAlignStr() const
{
    switch (getVerticalAlign()) {
    case EVerticalAlign::center:
        return "center";
    case EVerticalAlign::top:
        return "top";
    case EVerticalAlign::bottom:
        return "bottom";
    default:
        return "undefined";
    }
}

void CRectangleText::setFontAlign(EHorizontalAlign hAlign)
{
    m_hAlign = hAlign;
}

EHorizontalAlign CRectangleText::getHorizontalAlign() const
{
    return m_hAlign;
}

void CRectangleText::setHorizontalAlign(const std::string &align)
{
    if (align == "center")
        setFontAlign(EHorizontalAlign::center);
    else if (align == "left")
        setFontAlign(EHorizontalAlign::left);
    else if (align == "right")
        setFontAlign(EHorizontalAlign::right);
    //else
    // TODO: Обработка ситуации неправильного ввода
}

std::string CRectangleText::getHorizontalAlignStr() const
{
    switch (getHorizontalAlign()) {
    case EHorizontalAlign::center:
        return "center";
    case EHorizontalAlign::left:
        return "left";
    case EHorizontalAlign::right:
        return "right";
    default:
        return "undefined";
    }
}

void CRectangleText::setText(const std::string &text)
{
    this->m_text = text;
}

std::string CRectangleText::getText() const
{
    return m_text;
}

void CRectangleText::addSymbol(char symbol)
{
    CRectangleSymbol *s = new CRectangleSymbol(symbol, &m_font, m_width, m_height, m_fontHeight, this);
    m_symbols.insert(s);
    s->prepare();
}

} // namespace behemoth
