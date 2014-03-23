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

#include "shaderfactory.h"

#include "core/lua/resourcemanager.h"
#include "core/ogl/ogl.h"

#include <fstream>
#include <iostream>

namespace behemoth {

CShaderFactory *CShaderFactory::instance = nullptr;

class __CShaderFactoryImplDel {
public:
    explicit __CShaderFactoryImplDel(CShaderFactory *shaderFactory) : shaderFactory(shaderFactory) {}
    ~__CShaderFactoryImplDel() {delete shaderFactory;}
private:
    CShaderFactory *shaderFactory;
};

CShaderFactory *CShaderFactory::getInstance()
{
    if (!instance) {
        instance = new CShaderFactory();
        static __CShaderFactoryImplDel delHelper(instance);
    }
    return instance;
}

CShaderFactory::CShaderFactory() : prefix(behemoth::CResourceManager::getInstance()->getShaderFolder()
    + behemoth::CResourceManager::getInstance()->getFileSeparator()), shaders(), activeShader(nullptr)
{
}

CShaderFactory::~CShaderFactory()
{
}

CShader *CShaderFactory::getShader(const std::string &name)
{
    std::map< std::string, std::shared_ptr<CShader> >::const_iterator it
            = shaders.find(name);
    if (it != shaders.end())
        return changeActiveShader(it->second.get());

    std::shared_ptr<CShader> shader = std::shared_ptr<CShader>(new CShader(name));
    if (!prepareShader(shader.get(), prefix + name + ".vert", prefix + name + ".frag"))
        return nullptr;
    shaders.insert(std::pair< std::string, std::shared_ptr<CShader> >(name, shader));
    return changeActiveShader(shader.get());
}

bool CShaderFactory::prepareShader(CShader *shader, const std::string &vertShaderName, const std::string &fragmentShaderName)
{
    shader->shaderProgram = glCreateProgram();

    if (!shader->shaderProgram)
        return false;

    std::string vs((std::istreambuf_iterator<char>(*(std::auto_ptr<std::ifstream>(
            new std::ifstream(vertShaderName))).get())), std::istreambuf_iterator<char>());
    int size = vs.size();
    if (!makeShader(shader, EShaderType::VertexShader, vs.c_str(), &size))
        return false;

    std::string fs((std::istreambuf_iterator<char>(*(std::auto_ptr<std::ifstream>(
            new std::ifstream(fragmentShaderName))).get())), std::istreambuf_iterator<char>());
    size = fs.size();
    if (!makeShader(shader, EShaderType::FragmentShader, fs.c_str(), &size))
        return false;

    glLinkProgram(shader->shaderProgram);

    if (!checkLinkStatus(shader))
        return false;

    glValidateProgram(shader->shaderProgram);
    return checkValidateStatus(shader);
}

bool CShaderFactory::makeShader(CShader *shader, EShaderType type, const char *source, int *sizes)
{
    if (type == EShaderType::VertexShader) {
        shader->vertexShader = glCreateShader(GL_VERTEX_SHADER);

        if (!shader->vertexShader)
            return false;

        glShaderSource(shader->vertexShader, 1, &source, sizes);
        glCompileShader(shader->vertexShader);

        if (!checkCompileShaderStatus(shader, shader->vertexShader))
            return false;

        appendShader(shader, EShaderType::VertexShader);
    } else if (type == EShaderType::FragmentShader) {
        shader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        if (!shader->fragmentShader)
            return false;

        glShaderSource(shader->fragmentShader, 1, &source, sizes);
        glCompileShader(shader->fragmentShader);

        if (!checkCompileShaderStatus(shader, shader->fragmentShader))
            return false;

        appendShader(shader, EShaderType::FragmentShader);
    }
    return true;
}

void CShaderFactory::appendShader(CShader *shader, EShaderType type)
{
    if (type == EShaderType::VertexShader)
        glAttachShader(shader->shaderProgram, shader->vertexShader);
    else if (type == EShaderType::FragmentShader)
        glAttachShader(shader->shaderProgram, shader->fragmentShader);
}

bool CShaderFactory::checkCompileShaderStatus(CShader *program, uint shader)
{
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        handleError(program, shader);
        return false;
    }
    return true;
}

bool CShaderFactory::checkLinkStatus(CShader *shader)
{
    int status;
    glGetProgramiv(shader->shaderProgram, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        handleError(shader, shader->shaderProgram);
        return false;
    }
    return true;
}

bool CShaderFactory::checkValidateStatus(CShader *shader)
{
    int status;
    glGetProgramiv(shader->shaderProgram, GL_VALIDATE_STATUS, &status);
    if(status == GL_FALSE) {
        handleError(shader, shader->shaderProgram);
        return false;
    }
    return true;
}

void CShaderFactory::handleError(CShader *program, uint shader)
{
    //! TODO: Залогировать!
    //! TODO: Вывод в лог ошибки, что за нах
    int maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(program->shaderProgram);
    program->shaderProgram = 0;
    glDeleteShader(program->vertexShader);
    program->vertexShader = 0;
    glDeleteShader(program->fragmentShader);
    program->fragmentShader = 0;

    for (int i = 0, n = infoLog.size(); i < n; ++i)
        std::cout << infoLog[i];
}

CShader *CShaderFactory::changeActiveShader(CShader *newShader)
{
    if (activeShader && activeShader->id != newShader->id) {
        activeShader->disable();
        activeShader = newShader;
        activeShader->bind();
    } else {
        activeShader = newShader;
        activeShader->bind();
    }
    return activeShader;
}

} // namespace behemoth
