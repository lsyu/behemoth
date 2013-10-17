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

#include "resourcemanager.h"

#include "core/algorithm/algostring.h"
#include "core/manager/luamanager.h"

#include <fstream>

namespace Core {

using namespace std;

ResourceManager *ResourceManager::instance = nullptr;

class __ResourceManagerImplDel {
public:
    explicit __ResourceManagerImplDel(ResourceManager *resourceManager) : resourceManager(resourceManager) {}
    ~__ResourceManagerImplDel() {delete resourceManager;}
private:
    ResourceManager *resourceManager;
};


ResourceManager* ResourceManager::getInstance()
{
    if (!instance) {
        instance = new ResourceManager;
        static __ResourceManagerImplDel deleteHelper(instance);
        LuaManager::getInstance()->readConfFile("core.conf");
        //instance->readConfigurationFile("core.conf");
    }
    return instance;
}

ResourceManager::ResourceManager() : mapOfParam(std::map<std::string, std::string>()) {}
ResourceManager::~ResourceManager() {}

bool ResourceManager::readConfigurationFile(const string &name)
{
    mapOfParam.clear();
    LuaManager::getInstance()->doFile(name);
    if (mapOfParam.empty()) {
        ifstream file(name);
        if (!file.is_open())
            return false;

        try {
            while (file.good()) {
                std::string line;
                getline(file, line);
                std::vector<std::string> list = Algorithm::Str::splitAndSpaceRemove(line, ':');
                if (list.size() > 1)
                    mapOfParam[list[0]] = list[1];
            }
        } catch (...) {
            file.close();
            return false;
        }
        file.close();
        return true;
    }
    return false;
}

string ResourceManager::getMeshFolder() const
{
    if (mapOfParam.find("mesh") != mapOfParam.end())
        return mapOfParam.at("mesh");
    return "";
}

string ResourceManager::getMaterialFolder() const
{
    if (mapOfParam.find("material") != mapOfParam.end())
        return mapOfParam.at("material");
    return "";
}

string ResourceManager::getShaderFolder() const
{
    if (mapOfParam.find("shader") != mapOfParam.end())
        return mapOfParam.at("shader");
    return "";
}

string ResourceManager::getTextureFolder() const
{
    if (mapOfParam.find("texture") != mapOfParam.end())
        return mapOfParam.at("texture");
    return "";
}

string ResourceManager::getFileSeparator() const
{
    return string("/");
}

} // namespace Core
