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

#include "rectanglesymbol.h"
#include "rectangletext.h"
#include "core/ogl/ogl.h"
#include "core/ogl/texturefactory.h"
#include "core/ogl/shaderfactory.h"
#include "core/fonts/fontfactory.h"

namespace core {

CRectangleSymbol::CRectangleSymbol(char symbol, CFont *font, float parentWidth, float parentHeight,
    float fontHeight, CRectangleText *parent) :CRectangle(), font(font), symbol(symbol),
    parentWidth(parentWidth), parentHeight(parentHeight), fontHeight(fontHeight), lineNumber(0)
{
    parent->addChild(this);
    texture = CTextureFactory::getInstance()->getSymbol(symbol, *font);

    float scHeight = (parent->getYMax() - parent->getYMin()) / 2.0f;
    float width = static_cast<float>(texture.getSize().x);
    float height = static_cast<float>(texture.getSize().y);
    this->width = symbol == '\n' ? 0 : font->getHeight() * width / height * scHeight;
    this->height = font->getHeight() * scHeight;
}

CRectangleSymbol::~CRectangleSymbol()
{
}

void CRectangleSymbol::paint() const
{
    vao.bind();
    glDrawArrays(GL_QUADS, 0, 4);
    vao.disable();
}

void CRectangleSymbol::onClicked(const CEventMouseClick &event)
{
}

bool CRectangleSymbol::operator >(CRectangleSymbol *other) const
{
    return this->symbol > other->symbol;
}

void CRectangleSymbol::configure()
{
    vPos2[0] = glm::vec2(x, y);
    vPos2[1] = glm::vec2(x + width, y);
    vPos2[2] = glm::vec2(x + width, y + height);
    vPos2[3] = glm::vec2(x, y + height);

    CShader *shader = CShaderFactory::getInstance()->getShader("text");
    if (shader) {
        vao.genBuffer();
        vao.bind();

        vertex.genBuffer();
        vertex.setData(&vPos2);
        shader->setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

        uv.genBuffer();
        uv.setData(&vUV);
        shader->setAttribute("UV", 2, 0, (const void*)0, GL_FLOAT);

        vao.disable();
    }
}

void CRectangleSymbol::prepare()
{
    std::vector<CBasic2dEntity*> &e = this->parent->getChilds();
    bool first = !(e.size()-1);
    CBasic2dEntity *parent = first ? this->parent : e[e.size()-2];
    x = first ? parent->getXMin() : parent->getXMax();
    y = first? parent->getYMax() - height : parent->getYMin();

    std::vector< std::vector<CRectangleSymbol*> > *vec
            = &dynamic_cast<CRectangleText*>(this->parent)->lines;
    if (x >= this->parent->getXMax() || x + width >= this->parent->getXMax() || symbol == '\n') {
        x = this->parent->getXMin();
        y = parent->getYMin() - height;
        if (vec->back().size())
            vec->push_back(std::vector<CRectangleSymbol*>());
    }
    vec->back().push_back(this);
    lineNumber = vec->size()-1;
}

void CRectangleSymbol::translate(const glm::vec2 &translate)
{
    x += translate.x;
    y += translate.y;
}

} // namespace core
