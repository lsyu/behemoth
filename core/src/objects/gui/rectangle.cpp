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

#include "rectangle.h"
#include "entity2dfactory.h"

#include "core/ogl/ogl.h"
#include "core/ogl/shaderfactory.h"
#include "core/ogl/texturefactory.h"
#include "core/application/application.h"
#include "core/events/eventmouseclick.h"

#include <iostream>

namespace behemoth {

CRectangle::CRectangle() : CRectangle("")
{
}

CRectangle::CRectangle(const std::string &id) : CBasic2dEntity(id),
    m_aspect(CApplication::getInstance()->getAspectRatio()), m_alpha(1.0f),
    m_size(glm::vec4(-1, -1, 2, 2)), m_border(), m_radius(), m_texture(nullptr), m_text()
{
    m_vertices.reserve(4);
    m_vertices = {
      //|  position              |  uv                    | colors                    |
        {glm::vec2(-1.0f, -1.0f), glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec2(-1.0f, 1.0f),  glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec2(1.0f, 1.0f),   glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec2(1.0f, -1.0f),  glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)}};
}

CRectangle::~CRectangle()
{
}

void CRectangle::configure()
{
    if (m_parent) {
        float scWidth = (m_parent->getXMax() - m_parent->getXMin()) / 2.0f;
        float scHeight = (m_parent->getYMax() - m_parent->getYMin()) / 2.0f;
        float shiftX = (m_parent->getXMax() + m_parent->getXMin()) / 2.0f;
        float shiftY = (m_parent->getYMax() + m_parent->getYMin()) / 2.0f;

        m_size.x = m_size.x * scWidth + shiftX;
        m_size.y = m_size.y * scHeight + shiftY;
        m_size.z *=  scWidth;
        m_size.w *= scHeight;
    }

    float halfOfMinSide = 0.5f * std::min(m_size.z, m_size.w);
    m_radius = m_radius * halfOfMinSide;

    m_border.width *= std::min(m_size.z, m_size.w) * 0.5f;

    m_vertices[0].vertex = glm::vec2(m_size.x, m_size.y);
    m_vertices[1].vertex = glm::vec2(m_size.x + m_size.z, m_size.y);
    m_vertices[2].vertex = glm::vec2(m_size.x + m_size.z, m_size.y + m_size.w);
    m_vertices[3].vertex = glm::vec2(m_size.x, m_size.y + m_size.w);

    if (m_texture && m_texture->getId()) {
        m_vertices[0].uv =  glm::vec2(0.0f, 1.0f - 0.0f);
        m_vertices[1].uv =  glm::vec2(1.0f, 1.0f - 0.0f);
        m_vertices[2].uv =  glm::vec2(1.0f, 1.0f - 1.0f);
        m_vertices[3].uv =  glm::vec2(0.0f, 1.0f - 1.0f);
    }

    CShader *shader = CShaderFactory::getInstance()->getShader("gui");
    if (shader) {
        m_vao.genBuffer();
        m_vao.bind();

        m_vertexVBO.genBuffer();
        m_vertexVBO.setData(&m_vertices);

        shader->setAttribute("a_position", 2, 0, sizeof(CVertex2D));
        shader->setAttribute("a_uv", 2, 8, sizeof(CVertex2D));
        shader->setAttribute("a_color", 3, 16, sizeof(CVertex2D));

        m_vao.disable();
    }

    for (auto child: m_childs)
        child->configure();
}

void CRectangle::paint() const
{
    CShader *shader = CShaderFactory::getInstance()->getShader("gui");
    if (shader && m_alpha > 0.0f) {
        shader->setUniform("aspect", m_aspect);
        shader->setUniform("alpha", m_alpha);
        shader->setUniform("size", m_size);
        shader->setUniform("radius", m_radius.toVec4());
        shader->setUniform("border", m_border.toVec4());

        if (m_texture && m_texture->getId()) {
            shader->setUniform("texture", 0);
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture->getId());
        }

        m_vao.bind();
        glDrawArrays(GL_QUADS, 0, 4);
        m_vao.disable();

        if (m_texture && m_texture->getId())
            glDisable(GL_TEXTURE_2D);
    }

    for (int i = m_childs.size()-1; i >= 0; --i)
        m_childs[i]->paint();
}

void CRectangle::setColor(const glm::vec3 &color)
{
    m_vertices[0].color = m_vertices[1].color = m_vertices[2].color = m_vertices[3].color = color;
}

bool CRectangle::contains(const glm::vec2 &point) const
{
    if (point.x < m_size.x || point.x > m_size.x+m_size.z)
        return false;
    if (point.y < m_size.y || point.y > m_size.y+m_size.w)
        return false;
    return true;
}

void CRectangle::onClicked(const CEventMouseClick &event)
{
    if (contains(event.getCoordinates()))
        CEntity2dFactory::getInstance()->getEntities4Event().push_back(this);
    for (int i = m_childs.size()-1; i >= 0; --i)
        dynamic_cast<CBasic2dEntity*>(m_childs[i])->onClicked(event);
}

glm::vec3 CRectangle::getColor() const
{
    return m_vertices[0].color;
}

float CRectangle::getXMin() const
{
    return m_size.x;
}

float CRectangle::getXMax() const
{
    return m_size.x + m_size.z;
}

float CRectangle::getYMin() const
{
    return m_size.y;
}

float CRectangle::getYMax() const
{
    return m_size.y + m_size.w;
}

void CRectangle::setX(float x)
{
    m_size.x = x;
}

void CRectangle::setY(float y)
{
    m_size.y = y;
}

void CRectangle::setWidth(float width)
{
    m_size.z = std::abs(width);
}

float CRectangle::getWidth() const
{
    return m_size.z;
}

void CRectangle::setHeight(float height)
{
    m_size.w = std::abs(height);
}

float CRectangle::getHeight() const
{
    return m_size.w;
}

void CRectangle::setRadius(const CBorderRadius &radius)
{
    m_radius = radius;
}

CBorderRadius CRectangle::getRadius() const
{
    return m_radius;
}

void CRectangle::setBorder(const CBorder &border)
{
    this->m_border = border;
}

CBorder CRectangle::getBorder() const
{
    return m_border;
}

void CRectangle::setTexture(const std::string &name)
{
    this->m_texture = CTextureFactory::getInstance()->getTexture(name);
}

std::string CRectangle::getTexture() const
{
    return m_texture->getFileName();
}

void CRectangle::setGradient(const CGradient &gradient)
{
    m_vertices[0].color = gradient.m_bottomLeft;
    m_vertices[3].color = gradient.m_topLeft;
    m_vertices[2].color = gradient.m_topRight;
    m_vertices[1].color = gradient.m_bottomRight;
}

CGradient CRectangle::getGradient() const
{
    return CGradient(m_vertices[0].color, m_vertices[3].color, m_vertices[2].color, m_vertices[1].color);
}

// от 0 до 1
float validateValue(float val)
{
    if (val < 0.0)
        val *= -1.0f;
    if (val > 1.0f)
        val -= static_cast<float>(static_cast<int>(val));
    return val;
}

void CRectangle::setAlpha(float alpha)
{
    this->m_alpha = validateValue(alpha);
}

float CRectangle::getAlpha() const
{
    return m_alpha;
}

void CRectangle::setText(const CRectangleText &text)
{
    this->m_text = text;
    addChild(&this->m_text);
}

CRectangleText CRectangle::getText() const
{
    return m_text;
}

} // namespace behemoth
