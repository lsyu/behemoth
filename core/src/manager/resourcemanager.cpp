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
    }
    return instance;
}

void CResourceManager::initialize(int &argc, char *argv[])
{
    patchToApplication = std::string(argv[0]);
    size_t len = patchToApplication.find_last_of(getFileSeparator());
    patchToApplication = patchToApplication.substr(0, len);
    CLuaManager::getInstance()->readConfFile(getCoreConf());
}

CResourceManager::CResourceManager() : mapOfParam(std::map<std::string, std::string>()) {}
CResourceManager::~CResourceManager() {}

string CResourceManager::getPatchToApplication() const
{
    return patchToApplication + getFileSeparator();
}

string CResourceManager::getResource(const string &name) const
{
    if (mapOfParam.find(name) != mapOfParam.end())
        return getPatchToApplication() + mapOfParam.at(name);
    return getPatchToApplication();
}

string CResourceManager::getCoreConf() const
{
    return getPatchToApplication() + std::string("core.conf");
}

string CResourceManager::getMeshFolder() const
{
    return getResource("mesh");
}

string CResourceManager::getMaterialFolder() const
{
    return getResource("material");
}

string CResourceManager::getShaderFolder() const
{
    return getResource("shader");
}

string CResourceManager::getTextureFolder() const
{
    return getResource("texture");
}

string CResourceManager::getFontFolder() const
{
    return getResource("font");
}

string CResourceManager::getFileSeparator() const
{
    // TODO: кроссплатформенно!
    return string("/");
}

} // namespace Core
