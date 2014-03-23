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

#include "rectangle.h"

#include "core/ogl/ogl.h"
#include "core/ogl/shaderfactory.h"
#include "core/ogl/texturefactory.h"
#include "core/application/application.h"
#include "core/events/eventmouseclick.h"

#include <iostream>

namespace core {

CRectangle::CRectangle() : CBasic2dEntity(), vao(), vertex(), color(), uv(), aspect(),
    x(-1), y(-1), width(1), height(1), rA(0.0f), rB(0.0f), rC(0.0f), rD(0.0f), alpha(1.0f),
    texture(), radius(), border(), text()
{
    vPos2.reserve(4);
    vColor.reserve(4);
    vUV.reserve(4);

    vPos2 = {
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(-1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, -1.0f)
    };

    vColor = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };

    // Перевернутое
    vUV = {
        glm::vec2(0.0f, 1.0f - 0.0f),
        glm::vec2(1.0f, 1.0f - 0.0f),
        glm::vec2(1.0f, 1.0f - 1.0f),
        glm::vec2(0.0f, 1.0f - 1.0f)
    };

    rA = rB = rC = rD = 0.0f;
    glm::ivec2 size = CApplication::getInstance()->getSize();
    aspect = size.y != 0.0f ? static_cast<float>(size.x) / static_cast<float>(size.y) : 1.0f;
}

CRectangle::CRectangle(const std::string &id) : CBasic2dEntity(id), vao(),
    vertex(), color(), uv(), aspect(), x(-1), y(-1), width(1), height(1), rA(0.0f), rB(0.0f),
    rC(0.0f), rD(0.0f), alpha(1.0f), texture(), radius(), border(), text()
{
    vPos2.reserve(4);
    vColor.reserve(4);
    vUV.reserve(4);

    vPos2 = {
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(-1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, -1.0f)
    };

    vColor = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };

    // Перевернутое
    vUV = {
        glm::vec2(0.0f, 1.0f - 0.0f),
        glm::vec2(1.0f, 1.0f - 0.0f),
        glm::vec2(1.0f, 1.0f - 1.0f),
        glm::vec2(0.0f, 1.0f - 1.0f)
    };

    rA = rB = rC = rD = 0.0f;
    glm::ivec2 size = CApplication::getInstance()->getSize();
    aspect = size.y != 0.0f ? static_cast<float>(size.x) / static_cast<float>(size.y) : 1.0f;
}

CRectangle::~CRectangle()
{
}

void CRectangle::configure()
{
    if (parent) {
        float scWidth = (parent->getXMax() - parent->getXMin()) / 2.0f;
        float scHeight = (parent->getYMax() - parent->getYMin()) / 2.0f;
        float shiftX = (parent->getXMax() + parent->getXMin()) / 2.0f;
        float shiftY = (parent->getYMax() + parent->getYMin()) / 2.0f;

        x = x * scWidth + shiftX;
        y = y * scHeight + shiftY;
        width = width * scWidth;
        height = height * scHeight;
    }

    float halfOfMinSide = 0.5f * std::min(width, height);
    rA *= halfOfMinSide;
    rB *= halfOfMinSide;
    rC *= halfOfMinSide;
    rD *= halfOfMinSide;

    float minR = 0.0f;
    minR = (rA > 0.0f && rB > 0.0f) ? std::min(rA, rB) : std::max(rA, rB);
    minR = (rC > 0.0f && minR > 0.0f) ? std::min(minR, rC) : std::max(minR, rC);
    minR = (rD > 0.0f && minR > 0.0f) ? std::min(minR, rD) : std::max(minR, rD);

    border.width *= std::min(width, height) * 0.5f;

    vPos2[0] = glm::vec2(x, y);
    vPos2[1] = glm::vec2(x + width, y);
    vPos2[2] = glm::vec2(x + width, y + height);
    vPos2[3] = glm::vec2(x, y + height);

    CShader *shader = CShaderFactory::getInstance()->getShader("gui");
    if (shader) {
        vao.genBuffer();
        vao.bind();

        vertex.genBuffer();
        vertex.setData(&vPos2);
        shader->setAttribute("position", 2, 0, 0);

        color.genBuffer();
        color.setData(&vColor);
        shader->setAttribute("color",3, 0, 0);

        if (texture.getId()) {
            uv.genBuffer();
            uv.setData(&vUV);
            shader->setAttribute("UV", 2, 0, 0);
        }

        vao.disable();
    }

    for (auto child: vChilds)
        child->configure();
}

void CRectangle::paint() const
{
    CShader *shader = CShaderFactory::getInstance()->getShader("gui");
    if (shader) {
        shader->setUniform("aspect", aspect);
        shader->setUniform("x", x);
        shader->setUniform("y", y);
        shader->setUniform("width", width);
        shader->setUniform("height", height);
        shader->setUniform("rA", rA);
        shader->setUniform("rB", rB);
        shader->setUniform("rC", rC);
        shader->setUniform("rD", rD);
        shader->setUniform("alpha", alpha);
        shader->setUniform("borderWidth", border.width);
        shader->setUniform("borderColor", border.color);

        if (texture.getId()) {
            shader->setUniform("textureUse", 1);
            shader->setUniform("texture", 0);
        } else {
            shader->setUniform("textureUse", 0);
        }

        if (texture.getId()) {
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.getId());
        }

        vao.bind();
        glDrawArrays(GL_QUADS, 0, 4);
        vao.disable();

        if (texture.getId())
            glDisable(GL_TEXTURE_2D);
    }

    for (int i = vChilds.size()-1; i >= 0; --i)
        vChilds[i]->paint();
}

void CRectangle::setColor(const glm::vec3 &color)
{
    vColor[0] = color;
    vColor[1] = color;
    vColor[2] = color;
    vColor[3] = color;
}

bool CRectangle::contains(const glm::vec2 &point) const
{
    if (point.x < x || point.x > x+width)
        return false;
    if (point.y < y || point.y > y+height)
        return false;
    return true;
}

void CRectangle::onClicked(const CEventMouseClick &event)
{
    if (contains(event.getCoordinates()))
        objects4Event.push_back(this);
    for (int i = vChilds.size()-1; i >= 0; --i)
        dynamic_cast<CBasic2dEntity*>(vChilds[i])->onClicked(event);
}

glm::vec3 CRectangle::getColor() const
{
    return vColor[0];
}

float CRectangle::getXMin() const
{
    return x;
}

float CRectangle::getXMax() const
{
    return x + width;
}

float CRectangle::getYMin() const
{
    return y;
}

float CRectangle::getYMax() const
{
    return y + height;
}

void CRectangle::setX(float x)
{
    this->x = x;
}

void CRectangle::setY(float y)
{
    this->y = y;
}

void CRectangle::setWidth(float width)
{
    this->width = std::abs(width);
}

float CRectangle::getWidth() const
{
    return width;
}

void CRectangle::setHeight(float height)
{
    this->height = std::abs(height);
}

float CRectangle::getHeight() const
{
    return height;
}

void CRectangle::setRadius(const CBorderRadius &radius)
{
    this->radius = radius;
    this->rA = radius.getBottomLeft();
    this->rB = radius.getTopLeft();
    this->rC = radius.getTopRight();
    this->rD = radius.getBottomRight();
}

CBorderRadius CRectangle::getRadius() const
{
    return radius;
}

void CRectangle::setBorder(const CBorder &border)
{
    this->border = border;
}

CBorder CRectangle::getBorder() const
{
    return border;
}

void CRectangle::setTexture(const std::string &name)
{
    this->texture = CTextureFactory::getInstance()->getTexture(name);
}

std::string CRectangle::getTexture() const
{
    return texture.getFileName();
}

void CRectangle::setGradient(const CGradient &gradient)
{
    vColor[0] = gradient.bottomLeft;
    vColor[1] = gradient.topLeft;
    vColor[2] = gradient.topRight;
    vColor[3] = gradient.bottomRight;
}

CGradient CRectangle::getGradient() const
{
    return CGradient(vColor[0], vColor[1], vColor[2], vColor[3]);
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
    this->alpha = validateValue(alpha);
}

float CRectangle::getAlpha() const
{
    return alpha;
}

void CRectangle::setText(const CRectangleText &text)
{
    this->text = text;
    addChild(&this->text);
}

CRectangleText CRectangle::getText() const
{
    return text;
}

} // namespace Core
