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
#include "core/factory/shaderfactory.h"
#include "core/factory/texturefactory.h"
#include "core/application.h"
#include "core/events/eventmouseclick.h"

#include <iostream>

namespace core {

CRectangle::CRectangle() : Basic2dEntity(), shader(nullptr), vao(), vertex(), color(), aspect(), x(-1), y(-1),
    width(1), height(1), rA(0.0f), rB(0.0f), rC(0.0f), rD(0.0f), alpha(1.0f), texture(0), textureName(),
    border(), text()
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

CRectangle::CRectangle(const std::string &id) : Basic2dEntity(id), shader(nullptr), vao(), vertex(),
    color(), aspect(), x(-1), y(-1), width(1), height(1), rA(0.0f), rB(0.0f), rC(0.0f), rD(0.0f),
    alpha(1.0f), texture(0),border()
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

    float halfOfMinSide = 0.5f * std::min(width, height)/* - 0.001f*/; // correct in min
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

    shader = CShaderFactory::getInstance()->getShader("test");

    vao.genBuffer();
    vao.bind();

    vertex.genBuffer();
    vertex.setData(&vPos2);
    shader->setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

    color.genBuffer();
    color.setData(&vColor);
    shader->setAttribute("color", 3, 0, (const void*)0, GL_FLOAT);

    if (texture) {
        uv.genBuffer();
        uv.setData(&vUV);
        shader->setAttribute("UV", 2, 0, (const void*)0, GL_FLOAT);
    }

    vao.disable();

    for (auto child: vChilds)
        child->configure();
}

void CRectangle::paint() const
{
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

    if (texture) {
        shader->setUniform("textureUse", 1);
        shader->setUniform("texture", 0);
    } else {
        shader->setUniform("textureUse", 0);
    }

    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    vao.bind();
    glDrawArrays(GL_QUADS, 0, 4);
    vao.disable();

    if (texture)
        glDisable(GL_TEXTURE_2D);

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
        dynamic_cast<Basic2dEntity*>(vChilds[i])->onClicked(event);
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

// от 0 до 1
float validateValue(float val)
{
    if (val < 0.0)
        val *= -1.0f;
    if (val > 1.0f)
        val -= static_cast<float>(static_cast<int>(val));
    return val;
}

void CRectangle::setRadius(float radius)
{
    radius = validateValue(radius);
    // TODO: Подумать, как исправить этот костыль (в связи с недетерминированной послед-тью в lua)
    if (rA == 0.0f)
        rA = radius;
    if (rB == 0.0f)
        rB = radius;
    if (rC == 0.0f)
        rC = radius;
    if (rD == 0.0f)
        rD = radius;
}

float CRectangle::getRadius() const
{
    return (rA + rB + rC + rD) / 4.0f;
}

void CRectangle::setRadiusOfA(float rA)
{
    this->rA = validateValue(rA);
}

float CRectangle::getRadiusOfA() const
{
    return rA;
}

void CRectangle::setRadiusOfB(float rB)
{
    this->rB = validateValue(rB);
}

float CRectangle::getRadiusOfB() const
{
    return rB;
}

void CRectangle::setRadiusOfC(float rC)
{
    this->rC = validateValue(rC);
}

float CRectangle::getRadiusOfC() const
{
    return rC;
}

void CRectangle::setRadiusOfD(float rD)
{
    this->rD = validateValue(rD);
}

float CRectangle::getRadiusOfD() const
{
    return rD;
}

void CRectangle::setBorderWidth(float width)
{
    this->border.width = validateValue(width);
}

float CRectangle::getBorderWidth() const
{
    return border.width;
}

void CRectangle::setBorderColor(const glm::vec3 &color)
{
    this->border.color = color;
}

glm::vec3 CRectangle::getBorderColor() const
{
    return border.color;
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
    this->textureName = name;
    this->texture = CTextureFactory::getInstance()->getTexture(name);
}

std::string CRectangle::getTexture() const
{
    return textureName;
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
