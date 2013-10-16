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

#include "luamanager.h"

#include "core/objects/entity.h"
#include "core/objects/2d/rectangle.h"

#include "glm/glm.h"

#include <iostream>
#include <sstream>

namespace Core {

LuaManager *LuaManager::instance = nullptr;

class __LuaManagerImplDel {
public:
    explicit __LuaManagerImplDel(LuaManager *luaManager) : luaManager(luaManager) {}
    ~__LuaManagerImplDel() {delete luaManager;}
private:
    LuaManager *luaManager;
};

LuaManager *LuaManager::getInstance()
{
    if (!instance) {
        instance = new LuaManager();
        static __LuaManagerImplDel delHelper(instance);
        instance->registerVec2();
        instance->registerVec3();
        instance->registerRectangle();
    }
    return instance;
}

LuaManager::LuaManager()
{
    init();
}

LuaManager::~LuaManager()
{
    close();
}

bool LuaManager::doFile(const std::string &file)
{
    if (!lua)
        init();
    bool ret = !luaL_dofile(lua, file.c_str());
    if(!ret)
        std::cout << "Lua error: " << luaL_checkstring(LuaManager::getInstance()->lua, -1) << std::endl;
    close();
    return ret;
}

void LuaManager::registerUI()
{
    //! TODO: Загрузка всех стандартных скриптов
    std::string tmp = "scripts/";
    luaL_dofile(lua, std::string(tmp + "vec.lua").c_str());
    luaL_dofile(lua, std::string(tmp + "ui.lua").c_str());
    luaL_dofile(lua, std::string(tmp + "triangle.lua").c_str());
    luaL_dofile(lua, std::string(tmp + "rectangle.lua").c_str());
}

void LuaManager::close()
{
    if (lua) {
        lua_close(lua);
        lua = nullptr;
        for(int i = 0, n = objects.size(); i < n; i++) {
            // Подготовим к работе
            objects[i]->configure();
        }
    }
}

void LuaManager::init()
{
    lua = luaL_newstate();
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
        registerUI();
    }
}

Core::Entity *LuaManager::getObject(const std::string &id)
{
    for(int i = 0, n = objects.size();i < n; i++) {
        if (objects[i]->getId() == id)
            return objects[i].get();
    }
    return nullptr;
}

Core::Entity *LuaManager::getObject(int num)
{
    if (num < 0 || num >= objects.size())
        return nullptr;
    return objects[num].get();
}

const std::vector< std::shared_ptr<Core::Entity> >& LuaManager::getObjects() const
{
    return objects;
}

template<class T>
void LuaManager::addObject(Entity *t)
{
    objects.push_back(std::shared_ptr<Entity>(dynamic_cast<T*>(t)));
}

//******************************!!!!!!!!!!!!!!!!!**********
void LuaManager::registerVec2()
{
    //! TODO: Сделать параметризацию загрузки
    luaL_Reg sFooRegs[] =
    {
        { "new", [](lua_State* l) -> int
          {
              float x = luaL_checknumber(l, 1);
              float y = luaL_checknumber(l, 2);
              glm::vec2 ** udata = static_cast<glm::vec2 **>(lua_newuserdata(l, sizeof(glm::vec2 *)));
              *udata = new glm::vec2(x, y);
              luaL_getmetatable(l, "luaL_Vec2");
              lua_setmetatable(l, -2);
              return 1;
          }
        },

        { "getX", [](lua_State* l) -> int
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              float res = foo->x;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "getY", [](lua_State* l) -> int
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              float res = foo->y;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "setX", [](lua_State* l) -> int
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              float x = luaL_checknumber(l, 2);
              foo->x = x;
              return 1;
          }
        },

        { "setY", [](lua_State* l) -> int
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              float y = luaL_checknumber(l, 2);
              foo->y = y;
              return 1;
          }
        },

        { "__gc", [](lua_State * l)
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              delete foo;
              return 0;
          }
        },

        { NULL, NULL }
    };
    luaL_newmetatable(lua, "luaL_Vec2");
    luaL_setfuncs (lua, sFooRegs, 0);
    lua_pushvalue(lua, -1);
    lua_setfield(lua, -1, "__index");
    lua_setglobal(lua, "Vec2");
}
//******************************!!!!!!!!!!!!!!!!!**********

//******************************!!!!!!!!!!!!!!!!!**********
void LuaManager::registerVec3()
{
    //! TODO: Сделать параметризацию загрузки
    luaL_Reg sFooRegs[] =
    {
        { "new", [](lua_State* l) -> int
          {
              float x = luaL_checknumber(l, 1);
              float y = luaL_checknumber(l, 2);
              float z = luaL_checknumber(l, 3);
              glm::vec3 ** udata = static_cast<glm::vec3 **>(lua_newuserdata(l, sizeof(glm::vec3 *)));
              *udata = new glm::vec3(x, y, z);
              luaL_getmetatable(l, "luaL_Vec3");
              lua_setmetatable(l, -2);
              return 1;
          }
        },

        { "getX", [](lua_State* l) -> int
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float res = foo->x;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "getY", [](lua_State* l) -> int
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float res = foo->y;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "getZ", [](lua_State* l) -> int
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float res = foo->z;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "setX", [](lua_State* l) -> int
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float x = luaL_checknumber(l, 2);
              foo->x = x;
              return 1;
          }
        },

        { "setY", [](lua_State* l) -> int
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float y = luaL_checknumber(l, 2);
              foo->y = y;
              return 1;
          }
        },

        { "setZ", [](lua_State* l) -> int
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float z = luaL_checknumber(l, 2);
              foo->z = z;
              return 1;
          }
        },

        { "__gc", [](lua_State * l)
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              delete foo;
              return 0;
          }
        },

        { NULL, NULL }
    };
    luaL_newmetatable(lua, "luaL_Vec3");
    luaL_setfuncs (lua, sFooRegs, 0);
    lua_pushvalue(lua, -1);
    lua_setfield(lua, -1, "__index");
    lua_setglobal(lua, "Vec3");
}
//******************************!!!!!!!!!!!!!!!!!**********

//******************************!!!!!!!!!!!!!!!!!**********
void LuaManager::registerRectangle()
{
    luaL_Reg sFooRegs[] =
    {
        {
            "new", [](lua_State *l) -> int
            {
                const char * id = luaL_checkstring(l, 1);
                Rectangle ** udata = static_cast<Rectangle **>(lua_newuserdata(l, sizeof(Rectangle *)));
                *udata = new Rectangle(id);
                luaL_getmetatable(l, "luaL_Rectangle");
                lua_setmetatable(l, -2);
                return 1;
            }
        },

        {
            "setX", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float x = luaL_checknumber(l, 2);
                foo->setX(x);
                return 1;
            }
        },

        {
            "setY", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float y = luaL_checknumber(l, 2);
                foo->setY(y);
                return 1;
            }
        },

        {
            "setWidth", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float width = luaL_checknumber(l, 2);
                foo->setWidth(width);
                return 1;
            }
        },

        {
            "setHeight", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float height = luaL_checknumber(l, 2);
                foo->setHeight(height);
                return 1;
            }
        },

        {
            "setRadius", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float radius = luaL_checknumber(l, 2);
                foo->setRadius(radius);
                return 1;
            }
        },

        {
            "setRadiusOfA", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rA = luaL_checknumber(l, 2);
                foo->setRadiusOfA(rA);
                return 1;
            }
        },

        {
            "setRadiusOfB", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rB = luaL_checknumber(l, 2);
                foo->setRadiusOfB(rB);
                return 1;
            }
        },

        {
            "setRadiusOfC", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rC = luaL_checknumber(l, 2);
                foo->setRadiusOfC(rC);
                return 1;
            }
        },

        {
            "setRadiusOfD", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rD = luaL_checknumber(l, 2);
                foo->setRadiusOfD(rD);
                return 1;
            }
        },

        {
            "setBorderWidth", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float border = luaL_checknumber(l, 2);
                foo->setBorderWidth(border);
                return 1;
            }
        },

        {
            "setBorderColor", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                glm::vec3 *color = *static_cast<glm::vec3 **>(luaL_checkudata(l, 2, "luaL_Vec3"));
                foo->setBorderColor(*color);
                return 1;
            }
        },

        {
            "setColor", [](lua_State *l) -> int
            {
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                glm::vec3 *color = *static_cast<glm::vec3 **>(luaL_checkudata(l, 2, "luaL_Vec3"));
                foo->setColor(*color);
                return 1;
            }
        },

        {
            "addChild", [](lua_State *l) -> int
            {
                // TODO: Подумать, как возвращать указатель на Entity
                Rectangle * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                Rectangle * bar = *static_cast<Rectangle **>(luaL_checkudata(l, 2, "luaL_Rectangle"));
                foo->addChild(bar);
                return 1;
            }
        },

        {
            "__gc", [](lua_State * l)
            {
                Entity * foo = *static_cast<Rectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                LuaManager::getInstance()->addObject<Rectangle>(foo);
                return 0;
            }
        },

        { NULL, NULL }
    };
    luaL_newmetatable(lua, "luaL_Rectangle");
    luaL_setfuncs (lua, sFooRegs, 0);
    lua_pushvalue(lua, -1);
    lua_setfield(lua, -1, "__index");
    lua_setglobal(lua, "Rectangle");
}
//******************************!!!!!!!!!!!!!!!!!**********

} // namespace Core


