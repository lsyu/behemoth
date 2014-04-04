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

#include "resourcemanager.h"
#include "luawrapper.h"

#include <fstream>

namespace behemoth {

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

void CResourceManager::initialize(int &/*argc*/, char *argv[])
{
    m_pathToApplication = std::string(argv[0]);
    size_t len = m_pathToApplication.find_last_of(getFileSeparator());
    m_pathToApplication = m_pathToApplication.substr(0, len) + getFileSeparator();
    luaL_dostring(m_lua, "conf = {}");
    registrationFolder();
    readConfFile();
}

void CResourceManager::registrationFolder()
{
    CLuaWrapper<CResourceManager> f(m_lua, "Folders");
    f.setNameSpace("conf");
    f.addProperty({"new", [](lua_State *l)
    {
        CResourceManager ** resMan
                = static_cast<CResourceManager **>(
                        lua_newuserdata(l, sizeof(CResourceManager *)));
        *resMan = CResourceManager::getInstance();
        luaL_getmetatable(l, "luaL_Folders");
        lua_setmetatable(l, -2);
        return 1;
    }});
    f.addProperty({"addResource", [](lua_State *l)
    {
        CResourceManager * foo = *static_cast<CResourceManager **>(luaL_checkudata(l, 1, "luaL_Folders"));
        const char *resName = luaL_checkstring(l, 2);
        const char *folder = luaL_checkstring(l, 3);
        foo->m_paths[resName] = folder;
        return 1;
    }});
    f.complete(false);
}

void CResourceManager::readConfFile()
{
    string confFile = m_pathToApplication + "core.conf";
    ifstream file(confFile.c_str());
    bool exists = file.good();
    file.close();
    if (exists) {
        luaL_dostring(m_lua,
                      "function conf:folders(data)\n"
                      "  local config = Folders.new()\n"
                      "  for k, v in pairs(data) do\n"
                      "    config:addResource(k, v)\n"
                      "  end\n"
                      "  return config\n"
                      "end");
        luaL_dofile(m_lua, confFile.c_str());
        closeLua();
    }
}

CResourceManager::CResourceManager() : CBasicLuaManager(),
    m_pathToApplication(), m_paths(std::map<std::string, std::string>())
{
}

CResourceManager::~CResourceManager() {}

string CResourceManager::getPatchToApplication() const
{
    return m_pathToApplication + getFileSeparator();
}

string CResourceManager::getResource(const string &name) const
{
    if (m_paths.find(name) != m_paths.end())
        return getPatchToApplication() + m_paths.at(name) + getFileSeparator();
    return getPatchToApplication() + "res" + getFileSeparator() + name + getFileSeparator();
}

string CResourceManager::getCoreConf() const
{
    return getPatchToApplication() + std::string("core.conf");
}

string CResourceManager::getMeshFolder() const
{
    return getResource("meshes");
}

string CResourceManager::getMaterialFolder() const
{
    return getResource("materials");
}

string CResourceManager::getShaderFolder() const
{
    return getResource("shaders");
}

string CResourceManager::getTextureFolder() const
{
    return getResource("textures");
}

string CResourceManager::getFontFolder() const
{
    return getResource("fonts");
}

std::string CResourceManager::getGUIFolder() const
{
    return getResource("gui");
}

string CResourceManager::getFileSeparator() const
{
    // TODO: кроссплатформенно!
    return string("/");
}

} // namespace behemoth
