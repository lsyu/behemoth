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

#include "rectanglefont.h"
#include "core/ogl/ogl.h"
#include "core/factory/texturefactory.h"
#include "core/factory/fontfactory.h"
#include "core/factory/shaderfactory.h"
#include "core/application.h"

namespace core {

CRectangleFont::CRectangleFont() : CRectangle(), font("UNKNOWN", 14), fontHeight(0.5f), buffer()
{
}

CRectangleFont::~CRectangleFont()
{
}

void CRectangleFont::configure()
{
    glm::ivec2 windowSize = CApplication::getInstance()->getSize();
    float pHeight = (parent->getYMax() - parent->getYMin())*windowSize.y*0.5;
    float pWidth = (parent->getXMax() - parent->getXMin())*windowSize.x*0.5;

    if (fontHeight > 1.0)
        fontHeight -= (int)fontHeight;

    fontHeight *= 2.0;

    this->font.setHeight(font.getQuantity());

    buffer = CFontFactory::getInstance()->getTextBuffer(text, font, pWidth, pHeight);
    texture = CTextureFactory::getInstance()->getTexture(buffer);

    width = pWidth * fontHeight / (float)windowSize.x;
    height = pHeight * fontHeight / (float)windowSize.y;

    x = parent->getXMin();
    y = parent->getYMin();

    if (font.getHorizontalAlign() == EHorizontalAlign::Left); // ничего не делаем
    else if (font.getHorizontalAlign() == EHorizontalAlign::Center)
        x += 0.5 * (parent->getXMax() - parent->getXMin() - width);
    else if (font.getHorizontalAlign() == EHorizontalAlign::Right)
        x += (parent->getXMax() - parent->getXMin() - width);
    if (font.getVerticalAlign() == EVerticalAlign::Bottom); // ничего не делаем
    else if (font.getVerticalAlign() == EVerticalAlign::Center)
        y += 0.5 * (parent->getYMax() - parent->getYMin() - height);
    else if (font.getVerticalAlign() == EVerticalAlign::Top)
        y += (parent->getYMax() - parent->getYMin() - height);

    vPos2[0] = glm::vec2(x, y);
    vPos2[1] = glm::vec2(x + width, y);
    vPos2[2] = glm::vec2(x + width, y + height);
    vPos2[3] = glm::vec2(x, y + height);

    shader = CShaderFactory::getInstance()->getShader("test");

    vao.genBuffer();
    vao.bind();

    vertex.genBuffer();
    vertex.setData(&vPos2);
    shader->setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

    color.genBuffer();
    color.setData(&vColor);
    shader->setAttribute("color", 3, 0, (const void*)0, GL_FLOAT);

    uv.genBuffer();
    uv.setData(&vUV);
    shader->setAttribute("UV", 2, 0, (const void*)0, GL_FLOAT);

    vao.disable();
}

void CRectangleFont::setFont(const CFont &font)
{
    this->font = font;
}

void CRectangleFont::setFont(const std::string &name)
{
    this->font.setName(name);
}

void CRectangleFont::setFont(float height)
{
    this->fontHeight = height;
}

void CRectangleFont::setFontQuantity(int quantity)
{
    this->font.setQuantity(quantity);
}

void CRectangleFont::setFontAlign(EVerticalAlign vAlign)
{
    this->font.setVericalAlign(vAlign);
}

void CRectangleFont::setFontAlign(EHorizontalAlign hAlign)
{
    this->font.setHorizontalAlign(hAlign);
}

void CRectangleFont::setText(const std::string &text)
{
    this->text = text;
}

} // namespace core
