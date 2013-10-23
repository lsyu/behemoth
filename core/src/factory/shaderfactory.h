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

#ifndef SHADERFACTORY_H
#define SHADERFACTORY_H

#include <memory>
#include <string>
#include <map>

#include "core/ogl/shader.h"

namespace core {

class __CShaderFactoryImplDel;

/**
 * @brief Фабрика получения шейдеров
 */
class CShaderFactory
{
public:
    friend class __CShaderFactoryImplDel;
    /**
     * @brief Получить экземпляр фабрики шейдеров.
     */
    static CShaderFactory * getInstance();
    /**
     * @brief Получить шейдер по имени.
     * @param name имя шейдера
     * @note В случае, если шейдер невозможно получить, вернется nullptr.
     */
    CShader* getShader(const std::string &name);
private:
    CShaderFactory();
    ~CShaderFactory();
    CShaderFactory(const CShaderFactory&);
    CShaderFactory &operator=(const CShaderFactory&);

    static CShaderFactory *instance;
    std::string prefix;
    std::map< std::string, std::shared_ptr<CShader> > shaders;
}; // class ShaderFactory

} // namespace Core

#endif // SHADERFACTORY_H
