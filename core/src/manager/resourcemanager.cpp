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

namespace core {

using namespace std;

CResourceManager *CResourceManager::instance = nullptr;

class __CResourceManagerImplDel {
public:
    explicit __CResourceManagerImplDel(CResourceManager *resourceManager) : resourceManager(resourceManager) {}
    ~__CResourceManagerImplDel() {delete resourceManager;}
private:
    CResourceManager *resourceManager;
};


CResourceManager* CResourceManager::getInstance()
{
    if (!instance) {
        instance = new CResourceManager;
        static __CResourceManagerImplDel deleteHelper(instance);
        CLuaManager::getInstance()->readConfFile("core.conf");
        //instance->readConfigurationFile("core.conf");
    }
    return instance;
}

CResourceManager::CResourceManager() : mapOfParam(std::map<std::string, std::string>()) {}
CResourceManager::~CResourceManager() {}

string CResourceManager::getMeshFolder() const
{
    if (mapOfParam.find("mesh") != mapOfParam.end())
        return mapOfParam.at("mesh");
    return "";
}

string CResourceManager::getMaterialFolder() const
{
    if (mapOfParam.find("material") != mapOfParam.end())
        return mapOfParam.at("material");
    return "";
}

string CResourceManager::getShaderFolder() const
{
    if (mapOfParam.find("shader") != mapOfParam.end())
        return mapOfParam.at("shader");
    return "";
}

string CResourceManager::getTextureFolder() const
{
    if (mapOfParam.find("texture") != mapOfParam.end())
        return mapOfParam.at("texture");
    return "";
}

string CResourceManager::getFileSeparator() const
{
    return string("/");
}

} // namespace Core
