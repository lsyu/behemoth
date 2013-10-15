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

#include "shaderfactory.h"

#include "core/manager/resourcemanager.h"

namespace Core {

std::shared_ptr<ShaderFactory> ShaderFactory::instance = nullptr;

ShaderFactory *ShaderFactory::getInstance()
{
    if (!instance)
        instance = std::shared_ptr<ShaderFactory>(new ShaderFactory());
    return instance.get();
}

ShaderFactory::ShaderFactory() : prefix(Core::ResourceManager::getInstance()->getShaderFolder()
        + Core::ResourceManager::getInstance()->getFileSeparator()), shaders()
{
}

ShaderFactory::~ShaderFactory()
{
}

Shader *ShaderFactory::getShader(const std::string &name)
{
    std::map< std::string, std::shared_ptr<Shader> >::const_iterator it
            = shaders.find(name);
    if (it != shaders.end())
        return it->second.get();


    std::shared_ptr<Shader> shader
            = std::shared_ptr<Shader>(new Shader(prefix + name + ".vert", prefix + name + ".frag"));
    shaders.insert(std::pair< std::string, std::shared_ptr<Shader> >(name, shader));
    return shader->isInit() ? shaders[name].get() : nullptr;
}

} // namespace Core
