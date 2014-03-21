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

#include "shader.h"

#include "core/ogl/ogl.h"

#include "glm/gtc/type_ptr.hpp"

namespace core {

CShader::CShader(const std::string &id) : cacheAttribute(), cacheUniform(), vertexShader(0), fragmentShader(0),
    shaderProgram(0), id(id)
{
}

CShader::~CShader()
{
    cacheAttribute.clear();
    cacheUniform.clear();
    if (shaderProgram)
        glDeleteProgram(shaderProgram);
    if (vertexShader)
        glDeleteShader(vertexShader);
    if (fragmentShader)
        glDeleteShader(fragmentShader);
}

uint CShader::makeAttributeLocation(const std::string &nameOfParam)
{
    int location;
    if (cacheAttribute.find(nameOfParam) != cacheAttribute.end()) {
        location = cacheAttribute[nameOfParam];
    } else {
        location = glGetAttribLocation(shaderProgram, nameOfParam.c_str());
        if (location != -1)
            cacheAttribute[nameOfParam] = location;
    }
    return static_cast<uint>(location);
}

void CShader::setAttribute(const std::string &nameOfParam, int numOfComponents, int stride,
        const void *ptr, uint type, bool normalized)
{
    uint location = makeAttributeLocation(nameOfParam);

    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, numOfComponents, type, normalized ? GL_TRUE : GL_FALSE,
            stride, ptr);
}

void CShader::setAttribute(const std::string &nameOfParam, float value)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib1f(location, value);
}

void CShader::setAttribute(const std::string &nameOfParam, const glm::vec2 &vec)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib2fv(location, &vec[0]);
}

void CShader::setAttribute(const std::string &nameOfParam, const glm::vec3 &vec)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib3fv(location, &vec[0]);
}

void CShader::setAttribute(const std::string &nameOfParam, const glm::vec4 &vec)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib4fv(location, &vec[0]);
}

int CShader::makeUniformLocation(const std::string &nameOfParam)
{
    int location;
    if (cacheUniform.find(nameOfParam) != cacheUniform.end()) {
        location = cacheUniform[nameOfParam];
    } else {
        location = glGetUniformLocation(shaderProgram, nameOfParam.c_str());
        if (location != -1)
            cacheUniform[nameOfParam] = location;
    }
    return location;
}

void CShader::setUniform(const std::string &nameOfParam, int value)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform1i(location, value);
}

void CShader::setUniform(const std::string &nameOfParam, float value)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform1f(location, value);
}

void CShader::setUniform(const std::string &nameOfParam, const glm::vec2 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform1fv(location, 2, &vec[0]);
}

void CShader::setUniform(const std::string &nameOfParam, const glm::vec3 &vec)
{
    // TODO: Так работает :)
    int location = makeUniformLocation(nameOfParam);
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void CShader::setUniform(const std::string &nameOfParam, const glm::vec4 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform1fv(location, 4, &vec[0]);
}

void CShader::setUniform(const std::string &nameOfParam, const glm::mat2 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform2fv(location, 2, &vec[0][0]);
}

void CShader::setUniform(const std::string &nameOfParam, const glm::mat3 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform3fv(location, 3, &vec[0][0]);
}

void CShader::setUniform(const std::string &nameOfParam, const glm::mat4 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(vec));
}

void CShader::bind() const
{
    glUseProgram(shaderProgram);
}

void CShader::disable() const
{
    glUseProgram(0);
}

} // namespace core
