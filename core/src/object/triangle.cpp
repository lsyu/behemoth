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

#include "triangle.h"

#include "core/ogl/ogl.h"

#include <iostream>

namespace Core {

Triangle::Triangle() : Entity(), shader(), vao(), vertex(), color() {}

Triangle::Triangle(const std::string &id) : Entity(id), shader(), vertex(), color()
{
    vPos2.reserve(3);
    vColor.resize(3);

    vPos2 = {
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, -1.0f)
    };

    vColor = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };
}

void Triangle::configure()
{
    shader.prepareShader("test.vert", "test.frag");

    vao.genBuffer();
    vao.bind();

    vertex.genBuffer();
    vertex.setData(&vPos2);
    shader.setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

    color.genBuffer();
    color.setData(&vColor);
    shader.setAttribute("color", 3, 0, (const void*)0, GL_FLOAT);

    vao.disable();
}

void Triangle::setPoint1(const glm::vec2 &p1)
{
    vPos2[0] = p1;
}

glm::vec2 Triangle::getPoint1() const
{
    return vPos2[0];
}

void Triangle::setPoint2(const glm::vec2 &p2)
{
    vPos2[1] = p2;
}

glm::vec2 Triangle::getPoint2() const
{
    return vPos2[1];
}
void Triangle::setPoint3(const glm::vec2 &p3)
{
    vPos2[2] = p3;
}

glm::vec2 Triangle::getPoint3() const
{
    return vPos2[2];
}

void Triangle::setColor1(const glm::vec3 &c1)
{
    vColor[0] = c1;
}

glm::vec3 Triangle::getColor1() const
{
    return vColor[0];
}

void Triangle::setColor2(const glm::vec3 &c2)
{
    vColor[1] = c2;
}

glm::vec3 Triangle::getColor2() const
{
    return vColor[1];
}

void Triangle::setColor3(const glm::vec3 &c3)
{
    vColor[2] = c3;
}

glm::vec3 Triangle::getColor3() const
{
    return vColor[2];
}

void Triangle::setColor(const glm::vec3 &color)
{
    vColor[0] = color;
    vColor[1] = color;
    vColor[2] = color;
}

void Triangle::paint() const
{
    shader.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.disable();
    shader.disable();
}
//Triangle::Triangle(const glm::vec2 &point1, const glm::vec2 &point2, const glm::vec2 &point3)
//{
//    shader.prepareShader("test.vert", "test.frag");
//    std::vector<glm::vec2> pos = {
//        point1,
//        point2,
//        point3
//    };
//    vertex.genBuffer();
//    vertex.setData(&pos);
//    shader.setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

//    std::vector<glm::vec3> col = {
//        glm::vec3(1.0f, 0.0f, 0.0f),
//        glm::vec3(1.0f, 0.0f, 0.0f),
//        glm::vec3(1.0f, 0.0f, 0.0f)
//    };
//    color.genBuffer();
//    color.setData(&col);
//    shader.setAttribute("color", 3, 0, (const void*)0, GL_FLOAT);
//}

//Triangle::Triangle(const glm::vec2 &point1, const glm::vec2 &point2, const glm::vec2 &point3,
//        const glm::vec3 &color)
//{
//    shader.prepareShader("test.vert", "test.frag");
//    std::vector<glm::vec2> pos = {
//        point1,
//        point2,
//        point3
//    };
//    vertex.genBuffer();
//    vertex.setData(&pos);
//    shader.setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

//    std::vector<glm::vec3> col = {
//        color,
//        color,
//        color
//    };
//    this->color.genBuffer();
//    this->color.setData(&col);
//    shader.setAttribute("color", 3, 0, (const void*)0, GL_FLOAT);
//}

//Triangle::Triangle(const glm::vec2 &point1, const glm::vec3 &color1, const glm::vec2 &point2,
//        const glm::vec3 &color2, const glm::vec2 &point3, const glm::vec3 color3)
//{
//    shader.prepareShader("test.vert", "test.frag");
//    std::vector<glm::vec2> pos = {
//        point1,
//        point2,
//        point3
//    };
//    vertex.genBuffer();
//    vertex.setData(&pos);
//    shader.setAttribute("position", 2, 0, (const void*)0, GL_FLOAT);

//    std::vector<glm::vec3> col = {
//        color1,
//        color2,
//        color3
//    };
//    this->color.genBuffer();
//    this->color.setData(&col);
//    shader.setAttribute("color", 3, 0, (const void*)0, GL_FLOAT);
//}

Triangle::~Triangle()
{
}

} // namespace Core
