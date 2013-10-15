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
#include "core/application.h"

namespace Core {

Rectangle::Rectangle() : Entity(), shader(nullptr), vao(), vertex(), color(), aspect(), x(-1), y(-1),
    width(1), height(1), rA(0.0f), rB(0.0f), rC(0.0f), rD(0.0f), border()
{
}

Rectangle::Rectangle(const std::string &id) : Entity(id), shader(nullptr), vao(), vertex(),
    color(), aspect(), x(-1), y(-1), width(1), height(1), rA(0.0f), rB(0.0f), rC(0.0f), rD(0.0f), border()
{
    vPos2.reserve(4);
    vColor.reserve(4);

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

    rA = rB = rC = rD = 0.0f;
    glm::ivec2 size = Application::getInstance()->getSize();
    aspect = size.y != 0.0f ? static_cast<float>(size.x) / static_cast<float>(size.y) : 1.0f;
}

Rectangle::~Rectangle()
{
}

void Rectangle::paint() const
{
    //shader->bind();
    shader->setUniform("aspect", aspect);
    shader->setUniform("x", x);
    shader->setUniform("y", y);
    shader->setUniform("width", width);
    shader->setUniform("height", height);
    shader->setUniform("rA", rA);
    shader->setUniform("rB", rB);
    shader->setUniform("rC", rC);
    shader->setUniform("rD", rD);
    shader->setUniform("borderWidth", border.width);
    shader->setUniform("borderColor", border.color);

    vao.bind();
    glDrawArrays(GL_QUADS, 0, 4);
    vao.disable();

    //shader->disable();

    for (int i = vChilds.size()-1; i >= 0; --i)
        vChilds[i]->paint();
}

void Rectangle::configure()
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

    float halfOfMinSide = 0.5f * std::min(width, height) - 0.001f;
    rA *= halfOfMinSide;
    rB *= halfOfMinSide;
    rC *= halfOfMinSide;
    rD *= halfOfMinSide;

    float minR = 0.0f;
    minR = (rA > 0.0f && rB > 0.0f) ? std::min(rA, rB) : std::max(rA, rB);
    minR = (rC > 0.0f && minR > 0.0f) ? std::min(minR, rC) : std::max(minR, rC);
    minR = (rD > 0.0f && minR > 0.0f) ? std::min(minR, rD) : std::max(minR, rD);

    border.width *= minR;

    vPos2[0] = glm::vec2(x, y);
    vPos2[1] = glm::vec2(x + width, y);
    vPos2[2] = glm::vec2(x + width, y + height);
    vPos2[3] = glm::vec2(x, y + height);

    shader = ShaderFactory::getInstance()->getShader("test");

    vao.genBuffer();
    vao.bind();

    vertex.genBuffer();
    vertex.setData(&vPos2);
    shader->setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

    color.genBuffer();
    color.setData(&vColor);
    shader->setAttribute("color", 3, 0, (const void*)0, GL_FLOAT);

    vao.disable();
}

void Rectangle::setColor(const glm::vec3 &color)
{
    vColor[0] = color;
    vColor[1] = color;
    vColor[2] = color;
    vColor[3] = color;
}

float Rectangle::getXMin() const
{
    return x;
}

float Rectangle::getXMax() const
{
    return x + width;
}

float Rectangle::getYMin() const
{
    return y;
}

float Rectangle::getYMax() const
{
    return y + height;
}

void Rectangle::setX(float x)
{
    this->x = x;
}

void Rectangle::setY(float y)
{
    this->y = y;
}

void Rectangle::setWidth(float width)
{
    this->width = std::abs(width);
}

void Rectangle::setHeight(float height)
{
    this->height = std::abs(height);
}

float validateRadius(float radius)
{
    if (radius < 0.0)
        radius *= -1.0f;
    if (radius > 1.0f)
        radius -= static_cast<float>(static_cast<int>(radius));
    return radius;
}

void Rectangle::setRadius(float radius)
{
    radius = validateRadius(radius);
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

void Rectangle::setRadiusOfA(float rA)
{

    this->rA = validateRadius(rA);
}

void Rectangle::setRadiusOfB(float rB)
{
    this->rB = validateRadius(rB);
}

void Rectangle::setRadiusOfC(float rC)
{
    this->rC = validateRadius(rC);
}

void Rectangle::setRadiusOfD(float rD)
{
    this->rD = validateRadius(rD);
}

void Rectangle::setBorderWidth(float width)
{
    this->border.width = validateRadius(width);
}

void Rectangle::setBorderColor(const glm::vec3 &color)
{
    this->border.color = color;
}

} // namespace Core
