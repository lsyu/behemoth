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

#include "core/algorithm/algostring.h"

#include "allegro5/allegro5.h"
#include "allegro5/allegro_opengl.h"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>

Shader::Shader() : cacheAttribute(), cacheUniform(), vertexShader(0), fragmentShader(0),
    shaderProgram(0), init(false)
{
}

Shader::Shader(const std::string &vertShaderName, const std::string &fragmentShaderName)
    : cacheAttribute(), cacheUniform(), vertexShader(0), fragmentShader(0), shaderProgram(0),
      init(false)
{
    prepareShader(vertShaderName, fragmentShaderName);
}

bool Shader::prepareShader(const std::string &vertShaderName, const std::string &fragmentShaderName)
{
    shaderProgram = glCreateProgram();

    if (!shaderProgram)
        return false;

    std::string vs = Algorithm::Str::getFile(vertShaderName);
    int size = vs.size();
    if (!makeShader(ShaderType::VertexShader, vs.c_str(), &size))
        return false;

    std::string fs = Algorithm::Str::getFile(fragmentShaderName);
    size = fs.size();
    if (!makeShader(ShaderType::FragmentShader, fs.c_str(), &size))
        return false;

    glLinkProgram(shaderProgram);

    if (!checkLinkStatus())
        return false;

    glValidateProgram(shaderProgram);

    if (!checkValidateStatus())
        return false;

    init = true;

    return true;
}

Shader::~Shader()
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

uint Shader::makeAttributeLocation(const std::string &nameOfParam)
{
    int location;
    if (cacheAttribute.find(nameOfParam) != cacheAttribute.end()) {
        location = cacheAttribute[nameOfParam];
    } else {
        location = glGetAttribLocation(shaderProgram, nameOfParam.c_str());
        if (location != -1)
            cacheAttribute[nameOfParam] = location;
        else
            throw ShaderException("undefined reference to attribute " + nameOfParam);
    }
    return static_cast<uint>(location);
}

void Shader::setAttribute(const std::string &nameOfParam, int numOfComponents, int stride,
        const void *ptr, uint type, bool normalized)
{
    uint location = makeAttributeLocation(nameOfParam);

    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, numOfComponents, type, normalized ? GL_TRUE : GL_FALSE,
            stride, ptr);
}

void Shader::setAttribute(const std::string &nameOfParam, float value)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib1f(location, value);
}

void Shader::setAttribute(const std::string &nameOfParam, const glm::vec2 &vec)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib2fv(location, &vec[0]);
}

void Shader::setAttribute(const std::string &nameOfParam, const glm::vec3 &vec)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib3fv(location, &vec[0]);
}

void Shader::setAttribute(const std::string &nameOfParam, const glm::vec4 &vec)
{
    uint location = makeAttributeLocation(nameOfParam);

    glVertexAttrib4fv(location, &vec[0]);
}

int Shader::makeUniformLocation(const std::string &nameOfParam)
{
    int location;
    if (cacheUniform.find(nameOfParam) != cacheUniform.end()) {
        location = cacheUniform[nameOfParam];
    } else {
        location = glGetUniformLocation(shaderProgram, nameOfParam.c_str());
        if (location != -1)
            cacheUniform[nameOfParam] = location;
        else
            throw ShaderException("undefined reference to uniform " + nameOfParam);
    }
    return location;
}

void Shader::setUniform(const std::string &nameOfParam, float value)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform1f(location, value);
}

void Shader::setUniform(const std::string &nameOfParam, const glm::vec2 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform1fv(location, 2, &vec[0]);
}

void Shader::setUniform(const std::string &nameOfParam, const glm::vec3 &vec)
{
    // TODO: Так работает :)
    int location = makeUniformLocation(nameOfParam);
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setUniform(const std::string &nameOfParam, const glm::vec4 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform1fv(location, 4, &vec[0]);
}

void Shader::setUniform(const std::string &nameOfParam, const glm::mat2 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform2fv(location, 2, &vec[0][0]);
}

void Shader::setUniform(const std::string &nameOfParam, const glm::mat3 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniform3fv(location, 3, &vec[0][0]);
}

void Shader::setUniform(const std::string &nameOfParam, const glm::mat4 &vec)
{
    int location = makeUniformLocation(nameOfParam);
    glUniformMatrix4fv(location, 1, GL_TRUE, glm::value_ptr(vec));
}

bool Shader::makeShader(ShaderType type, const char *source, int *sizes)
{
    if (type == ShaderType::VertexShader) {
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        if (!vertexShader)
            return false;

        glShaderSource(vertexShader, 1, &source, sizes);
        glCompileShader(vertexShader);

        if (!checkCompileShaderStatus(vertexShader))
            return false;

        appendShader(ShaderType::VertexShader);
    } else if (type == ShaderType::FragmentShader) {
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        if (!fragmentShader)
            return false;

        glShaderSource(fragmentShader, 1, &source, sizes);
        glCompileShader(fragmentShader);

        if (!checkCompileShaderStatus(fragmentShader))
            return false;

        appendShader(ShaderType::FragmentShader);
    }
    return true;
}

void Shader::appendShader(ShaderType type)
{
    if (type == ShaderType::VertexShader)
        glAttachShader(shaderProgram, vertexShader);
    else if (type == ShaderType::FragmentShader)
        glAttachShader(shaderProgram, fragmentShader);
}

void Shader::handleError(uint shader)
{
    //! TODO: Залогировать!
    //! TODO: Вывод в лог ошибки, что за нах
    int maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(shaderProgram);
    shaderProgram = 0;
    glDeleteShader(vertexShader);
    vertexShader = 0;
    glDeleteShader(fragmentShader);
    fragmentShader = 0;

    init = false;

    for (int i = 0, n = infoLog.size(); i < n; ++i)
        std::cout << infoLog[i];
}

bool Shader::checkCompileShaderStatus(uint shader)
{
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        handleError(shader);
        return false;
    }
    return true;
}

bool Shader::checkLinkStatus()
{
    int status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        handleError(shaderProgram);
        return false;
    }
    return true;
}

bool Shader::checkValidateStatus()
{
    int status;
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &status);
    if(status == GL_FALSE)
    {
        handleError(shaderProgram);
        return false;
    }
    return true;
}

bool Shader::isInit() const
{
    return init;
}

void Shader::bind() const
{
    glUseProgram(shaderProgram);
}

void Shader::disable() const
{
    glUseProgram(0);
}
