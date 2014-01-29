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
    pathToApplication = std::string(argv[0]);
    size_t len = pathToApplication.find_last_of(getFileSeparator());
    pathToApplication = pathToApplication.substr(0, len) + getFileSeparator();
    registrationFolder();
    readConfFile();
}

void CResourceManager::registrationFolder()
{
    luaL_Reg sFooRegs[] =
    {
        {
            "new", [](lua_State *l)
            {
                CResourceManager ** resMan
                        = static_cast<CResourceManager **>(
                                lua_newuserdata(l, sizeof(CResourceManager *)));
                *resMan = CResourceManager::getInstance();
                luaL_getmetatable(l, "luaL_Folders");
                lua_setmetatable(l, -2);
                return 1;
            }
        },

        {
            "addResource", [](lua_State *l)
            {
                CResourceManager * foo = *static_cast<CResourceManager **>(luaL_checkudata(l, 1, "luaL_Folders"));
                const char *resName = luaL_checkstring(l, 2);
                const char *folder = luaL_checkstring(l, 3);
                foo->mapOfParam[resName] = folder;
                return 1;
            }
        },

        "__gc", [](lua_State * l)
        {
            // Т.к CResourceManager синглтон, и он нам еще понадобится, ничего не удаляем!
            return 0;
        },

        { NULL, NULL }
    }; //luaL_Reg sFooRegs
    luaL_newmetatable(lua, "luaL_Folders");
    luaL_setfuncs (lua, sFooRegs, 0);
    lua_pushvalue(lua, -1);
    lua_setfield(lua, -1, "__index");
    lua_setglobal(lua, "Folders");
}

void CResourceManager::readConfFile()
{
    //! TODO: Загрузка всех скриптов для системы конфигурации
    std::string path = pathToApplication + "scripts" + getFileSeparator();
    luaL_dofile(lua, std::string(path + "conf.lua").c_str());
    luaL_dofile(lua, std::string(path + "folders.lua").c_str());
    luaL_dofile(lua, std::string(pathToApplication + "core.conf").c_str());
    lua_close(lua);
}

CResourceManager::CResourceManager() : pathToApplication(), mapOfParam(std::map<std::string, std::string>()),
        lua(luaL_newstate())
{
    if (lua) {
        const luaL_Reg lualibs[] =
        {
            { "base", luaopen_base },
            { LUA_IOLIBNAME, luaopen_io},
            { LUA_TABLIBNAME, luaopen_table},
            { NULL, NULL}
        };

        const luaL_Reg *lib = lualibs;
        for(; lib->func != NULL; lib++)
        {
            lib->func(lua);
            lua_settop(lua, 0);
        }
    }
}

CResourceManager::~CResourceManager() {}

string CResourceManager::getPatchToApplication() const
{
    return pathToApplication + getFileSeparator();
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
