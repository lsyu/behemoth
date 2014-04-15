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

#include "rectanglesymbol.h"
#include "rectangletext.h"
#include "core/ogl/ogl.h"
#include "core/ogl/texturefactory.h"
#include "core/ogl/shaderfactory.h"
#include "core/fonts/fontfactory.h"

namespace behemoth {

CRectangleSymbol::CRectangleSymbol(char symbol, CFont *font, float parentWidth, float parentHeight,
    float fontHeight, CRectangleText *parent) :CRectangle(), m_font(font), m_symbol(symbol),
    m_parentWidth(parentWidth), parentHeight(parentHeight), m_fontHeight(fontHeight), m_lineNumber(0)
{
    parent->addChild(this);
    m_texture = CTextureFactory::getInstance()->getSymbol(symbol, *font);

    float scHeight = (parent->getYMax() - parent->getYMin()) / 2.0f;
    float width = static_cast<float>(m_texture->getSize().x);
    float height = static_cast<float>(m_texture->getSize().y);
    m_size.z = symbol == '\n' ? 0 : font->getHeight() * width / height * scHeight;
    m_size.w = font->getHeight() * scHeight;
}

CRectangleSymbol::~CRectangleSymbol()
{
}

void CRectangleSymbol::paint() const
{
    m_vao.bind();
    glDrawArrays(GL_QUADS, 0, 4);
    m_vao.disable();
}

void CRectangleSymbol::onClicked(const CEventMouseClick &/*event*/)
{
}

bool CRectangleSymbol::operator >(CRectangleSymbol *other) const
{
    return this->m_symbol > other->m_symbol;
}

void CRectangleSymbol::configure()
{
    m_vertices[0].vertex = glm::vec2(m_size.x, m_size.y);
    m_vertices[1].vertex = glm::vec2(m_size.x + m_size.z, m_size.y);
    m_vertices[2].vertex = glm::vec2(m_size.x + m_size.z, m_size.y + m_size.w);
    m_vertices[3].vertex = glm::vec2(m_size.x, m_size.y + m_size.w);

    m_vertices[0].uv =  glm::vec2(0.0f, 1.0f - 0.0f);
    m_vertices[1].uv =  glm::vec2(1.0f, 1.0f - 0.0f);
    m_vertices[2].uv =  glm::vec2(1.0f, 1.0f - 1.0f);
    m_vertices[3].uv =  glm::vec2(0.0f, 1.0f - 1.0f);

    CShader *shader = CShaderFactory::getInstance()->getShader("text");
    if (shader) {
        m_vao.genBuffer();
        m_vao.bind();

        m_vertexVBO.genBuffer();
        m_vertexVBO.setData(&m_vertices);

        shader->setAttribute("a_position", 2, 0, sizeof(CVertex2D));
        shader->setAttribute("a_uv", 2, 8, sizeof(CVertex2D));
//        shader->setAttribute("a_color", 3, 16, sizeof(CVertex2D));

        m_vao.disable();
    }
}

void CRectangleSymbol::prepare()
{
    std::vector<CBasic2dEntity*> &e = this->m_parent->getChilds();
    bool first = !(e.size()-1);
    CBasic2dEntity *parent = first ? this->m_parent : e[e.size()-2];
    m_size.x = first ? parent->getXMin() : parent->getXMax();
    m_size.y = first? parent->getYMax() - m_size.w : parent->getYMin();

    std::vector< std::vector<CRectangleSymbol*> > *vec
            = &dynamic_cast<CRectangleText*>(this->m_parent)->m_lines;
    if (m_size.x >= this->m_parent->getXMax() || m_size.x + m_size.z >= this->m_parent->getXMax() || m_symbol == '\n') {
        m_size.x = this->m_parent->getXMin();
        m_size.y = parent->getYMin() - m_size.w;
        if (vec->back().size())
            vec->push_back(std::vector<CRectangleSymbol*>());
    }
    vec->back().push_back(this);
    m_lineNumber = vec->size()-1;
}

void CRectangleSymbol::translate(const glm::vec2 &translate)
{
    m_size.x += translate.x;
    m_size.y += translate.y;
}

} // namespace behemoth
