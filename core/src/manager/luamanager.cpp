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

#include "core/objects/abstractentity.h"
#include "core/objects/2d/rectangle.h"
#include "core/objects/2d/rectangletext.h"

#include "core/manager/resourcemanager.h"

#include "glm/glm.h"

#include <algorithm>
#include <iostream>

namespace core {

CLuaManager *CLuaManager::instance = nullptr;

class __CLuaManagerImplDel {
public:
    explicit __CLuaManagerImplDel(CLuaManager *luaManager) : luaManager(luaManager) {}
    ~__CLuaManagerImplDel() {delete luaManager;}
private:
    CLuaManager *luaManager;
};

CLuaManager *CLuaManager::getInstance()
{
    if (!instance) {
        instance = new CLuaManager();
        static __CLuaManagerImplDel delHelper(instance);
        // При инициализации хорошо бы прочитать, где что находится.
        // Важно, чтобы сначала прочитались ресурсы, а уже потом - объекты.
        instance->init(TaskConfig);
    }
    return instance;
}

CLuaManager::CLuaManager() : lua(), objects(), config()
{
}

CLuaManager::~CLuaManager()
{
}

bool CLuaManager::parseFile(const std::string &fileName, CurrentTask task)
{
    if (!lua)
        init(task);
    bool ret = !luaL_dofile(lua, fileName.c_str());
    // TODO: Залогировать
    if(!ret) {
        // TODO: Залогировать!
        std::cout << lua_tostring(lua, -1);
    }
    close(task);
    return ret;
}

bool CLuaManager::readGui(const std::string &file)
{
    return parseFile(file, TaskGUI);
}

bool CLuaManager::readConfFile(const std::string &file)
{
    return parseFile(file, TaskConfig);
}

void CLuaManager::registerUI()
{
    //! TODO: Загрузка всех скриптов объектов сцены
    std::string tmp = "scripts/";
    luaL_dofile(lua, std::string(tmp + "vec.lua").c_str());
    luaL_dofile(lua, std::string(tmp + "ui.lua").c_str());
    luaL_dofile(lua, std::string(tmp + "rectangletext.lua").c_str());
    luaL_dofile(lua, std::string(tmp + "rectangle.lua").c_str());


    registerVec2();
    registerVec3();
    registerText();
    registerRectangle();
}

void CLuaManager::registerConf()
{
    //! TODO: Загрузка всех скриптов для системы конфигурации
    std::string tmp = "scripts/";
    luaL_dofile(lua, std::string(tmp + "conf.lua").c_str());
    luaL_dofile(lua, std::string(tmp + "folders.lua").c_str());

    registerFolders();
}

void CLuaManager::close(CurrentTask task)
{
    if (lua) {
//        if (task == TaskGUI) {
//            lua_getglobal(lua, "ui");
//            if (lua_istable(lua, -1))
//            {
//                lua_getfield(lua, -1, "hideItem");
//                lua_getfield(lua, -1, "setAlpha");
//                lua_getfield(lua, -3, "hideItem");
//                lua_pushnumber(lua, 0.1);
//                //lua_replace(lua, -2);
//                if (lua_pcall(lua, 2, 0, 0)) {
//                    const char* err = lua_tostring(lua, -1);
//                    int a = 1+1;
//                }else
//                lua_pop(lua, 2);
//            }
//        }
        if (task == TaskConfig) {
            lua_close(lua);
            lua = nullptr;
        }
        if (task == TaskGUI) {
            // Подготовим к работе наши сущности UI
            for(auto obj: objects)
                obj->configure();
        }
    }
}

void CLuaManager::init(CurrentTask task)
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
        if (task == TaskGUI)
            registerUI();
        else if (task == TaskConfig)
            registerConf();
    }
}

core::AbstractEntity *CLuaManager::getObject(const std::string &id)
{
    std::vector< std::shared_ptr<core::AbstractEntity> >::iterator it
            = std::find_if(objects.begin(), objects.end(),
            [&id](const std::shared_ptr<core::AbstractEntity> &obj)
            {
                return obj->getId() == id;
            });
    return it != objects.end() ? static_cast<core::AbstractEntity*>(&(*it->get())) : nullptr;
}

core::AbstractEntity *CLuaManager::getObject(int num)
{
    if (num < 0 || num >= static_cast<int>(objects.size()))
        return nullptr;
    return objects[num].get();
}

const std::vector< std::shared_ptr<core::AbstractEntity> >& CLuaManager::getObjects() const
{
    return objects;
}

template<class T>
void CLuaManager::addObject(AbstractEntity *t)
{
    objects.push_back(std::shared_ptr<AbstractEntity>(dynamic_cast<T*>(t)));
}


void CLuaManager::registerVec2()
{
    //! TODO: Сделать параметризацию загрузки
    luaL_Reg sFooRegs[] =
    {
        { "new", [](lua_State* l)
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

        { "getX", [](lua_State* l)
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              float res = foo->x;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "getY", [](lua_State* l)
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              float res = foo->y;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "setX", [](lua_State* l)
          {
              glm::vec2 * foo = *static_cast<glm::vec2 **>(luaL_checkudata(l, 1, "luaL_Vec2"));
              float x = luaL_checknumber(l, 2);
              foo->x = x;
              return 1;
          }
        },

        { "setY", [](lua_State* l)
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

void CLuaManager::registerVec3()
{
    //! TODO: Сделать параметризацию загрузки
    luaL_Reg sFooRegs[] =
    {
        { "new", [](lua_State* l)
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

        { "getX", [](lua_State* l)
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float res = foo->x;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "getY", [](lua_State* l)
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float res = foo->y;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "getZ", [](lua_State* l)
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float res = foo->z;
              lua_pushnumber(l, res);
              return 1;
          }
        },

        { "setX", [](lua_State* l)
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float x = luaL_checknumber(l, 2);
              foo->x = x;
              return 1;
          }
        },

        { "setY", [](lua_State* l)
          {
              glm::vec3 * foo = *static_cast<glm::vec3 **>(luaL_checkudata(l, 1, "luaL_Vec3"));
              float y = luaL_checknumber(l, 2);
              foo->y = y;
              return 1;
          }
        },

        { "setZ", [](lua_State* l)
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

void CLuaManager::registerRectangle()
{
    luaL_Reg sFooRegs[] =
    {
        {
            "new", [](lua_State *l)
            {
                const char * id = luaL_checkstring(l, 1);
                CRectangle ** udata = static_cast<CRectangle **>(lua_newuserdata(l, sizeof(CRectangle *)));
                *udata = new CRectangle(id);
                luaL_getmetatable(l, "luaL_Rectangle");
                lua_setmetatable(l, -2);
                return 1;
            }
        },

        {
            "setX", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float x = luaL_checknumber(l, 2);
                foo->setX(x);
                return 1;
            }
        },

        {
            "setY", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float y = luaL_checknumber(l, 2);
                foo->setY(y);
                return 1;
            }
        },

        {
            "setWidth", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float width = luaL_checknumber(l, 2);
                foo->setWidth(width);
                return 1;
            }
        },

        {
            "setHeight", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float height = luaL_checknumber(l, 2);
                foo->setHeight(height);
                return 1;
            }
        },

        {
            "setRadius", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float radius = luaL_checknumber(l, 2);
                foo->setRadius(radius);
                return 1;
            }
        },

        {
            "setRadiusOfA", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rA = luaL_checknumber(l, 2);
                foo->setRadiusOfA(rA);
                return 1;
            }
        },

        {
            "setRadiusOfB", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rB = luaL_checknumber(l, 2);
                foo->setRadiusOfB(rB);
                return 1;
            }
        },

        {
            "setRadiusOfC", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rC = luaL_checknumber(l, 2);
                foo->setRadiusOfC(rC);
                return 1;
            }
        },

        {
            "setRadiusOfD", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float rD = luaL_checknumber(l, 2);
                foo->setRadiusOfD(rD);
                return 1;
            }
        },

        {
            "setBorderWidth", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float border = luaL_checknumber(l, 2);
                foo->setBorderWidth(border);
                return 1;
            }
        },

        {
            "setBorderColor", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                glm::vec3 *color = *static_cast<glm::vec3 **>(luaL_checkudata(l, 2, "luaL_Vec3"));
                foo->setBorderColor(*color);
                return 1;
            }
        },

        {
            "setColor", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                glm::vec3 *color = *static_cast<glm::vec3 **>(luaL_checkudata(l, 2, "luaL_Vec3"));
                foo->setColor(*color);
                return 1;
            }
        },

        {
            "setTexture", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                const char *textureName = luaL_checkstring(l, 2);
                foo->setTexture(textureName);
                return 1;
            }
        },

        {
            "setAlpha", [](lua_State *l)
            {
                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                float alpha = luaL_checknumber(l, 2);
                foo->setAlpha(alpha);
                return 1;
            }
        },

        {
            "addChild", [](lua_State *l)
            {

                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                AbstractEntity * bar = *static_cast<AbstractEntity **>(lua_touserdata(l, 2));//(luaL_checkudata(l, 2, "luaL_Rectangle"));
                foo->addChild(bar);
                return 1;
            }
        },

        {
            "sync", [](lua_State *l)
            {

                CRectangle * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));
                lua_newtable(l);//Создаем новую таблицу в Lua
                lua_pushstring(l,"__newindex");
                lua_pushlightuserdata(l, foo);
                lua_pushcclosure
                (
                    l,
                    [](lua_State *l){
                        std::string property = luaL_checkstring(l,2);
                        CRectangle *foo = *static_cast<CRectangle **>(lua_touserdata(l, 1));
                        if (property == "x")
                            foo->setX(lua_tonumber(l, -1));
                        else if (property == "y")
                            foo->setY(lua_tonumber(l, -1));
                        else if (property == "width")
                            foo->setWidth(lua_tonumber(l, -1));
                        else if (property == "height")
                            foo->setHeight(lua_tonumber(l, -1));
                        else if (property == "color") {
                            glm::vec3 *color = *static_cast<glm::vec3 **>(luaL_checkudata(l, 2, "luaL_Vec3"));
                            foo->setColor(*color);
                        } else if (property == "texture")
                            foo->setTexture(lua_tostring(l , -1));
                        else if (property == "radius")
                            foo->setRadius(lua_tonumber(l, -1));
                        else if (property == "radiusOfA")
                            foo->setRadiusOfA(lua_tonumber(l, -1));
                        else if (property == "radiusOfB")
                            foo->setRadiusOfB(lua_tonumber(l, -1));
                        else if (property == "radiusOfC")
                            foo->setRadiusOfC(lua_tonumber(l, -1));
                        else if (property == "radiusOfD")
                            foo->setRadiusOfD(lua_tonumber(l, -1));
                        else if (property == "alpha")
                            foo->setAlpha(lua_tonumber(l, -1));
                        else
                            return 0;
                        return 1;
                    },
                    1
                );
                lua_rawset(l, -3);
                lua_setmetatable(l,-2);
                lua_getmetatable(l, -1);
                lua_pushstring(l, "__index");
                lua_pushlightuserdata(l,foo);
                lua_pushcclosure
                (
                    l,
                    [](lua_State *l){
                        std::string property = luaL_checkstring(l, 2);
                        CRectangle *foo = *static_cast<CRectangle **>(lua_touserdata(l, 1));
                        if (property == "x")
                            lua_pushnumber(l, foo->getXMin());
                        else if (property == "y")
                            lua_pushnumber(l, foo->getYMin());
                        else if (property == "width")
                            lua_pushnumber(l, foo->getWidth());
                        else if (property == "height")
                            lua_pushnumber(l, foo->getHeight());
                        else if (property == "color") {
                            // TODO: Получение  цвета
                        } //else if (property == "texture")
                            // TODO: Получение текстуры
                        //else if (property == "radius")
                            // TODO: Получение радиусов
                        //else if (property == "radiusOfA")
                            // TODO: Получение радиусов
                        //else if (property == "radiusOfB")
                            // TODO: Получение радиусов
                        //else if (property == "radiusOfC")
                            // TODO: Получение радиусов
                        //else if (property == "radiusOfD")
                            // TODO: Получение радиусов
                        //else if (property == "alpha")
                            // TODO: Получение радиусов
                        else
                            return 0;
                        return 1;
                    },
                    1
                );
                lua_rawset(l, -3);
                lua_setmetatable(l, -2);//Устанавливаем метатаблицу для нашей новой таблицы
                lua_setglobal(l, "luaL_Rectangle");
                CLuaManager::getInstance()->addObject<CRectangle>(foo);
                return 1;
            }
        },

        {
            "__gc", [](lua_State * l)
            {
                //AbstractEntity * foo = *static_cast<CRectangle **>(luaL_checkudata(l, 1, "luaL_Rectangle"));

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

void CLuaManager::registerText()
{
    luaL_Reg sFooRegs[] =
    {
        {
            "new", [](lua_State *l)
            {
                CRectangleText ** udata = static_cast<CRectangleText **>(lua_newuserdata(l, sizeof(CRectangleText *)));
                *udata = new CRectangleText();
                luaL_getmetatable(l, "luaL_Text");
                lua_setmetatable(l, -2);
                return 1;
            }
        },

        {
            "setText", [](lua_State *l)
            {
                CRectangleText * foo = *static_cast<CRectangleText **>(luaL_checkudata(l, 1, "luaL_Text"));
                const char *text = luaL_checkstring(l, 2);
                foo->setText(text);
                return 1;
            }
        },

        {
            "setName", [](lua_State *l)
            {
                CRectangleText * foo = *static_cast<CRectangleText **>(luaL_checkudata(l, 1, "luaL_Text"));
                const char *fontName = luaL_checkstring(l, 2);
                foo->setFont(fontName);
                return 1;
            }
        },

        {
            "setHeight", [](lua_State *l)
            {
                CRectangleText * foo = *static_cast<CRectangleText **>(luaL_checkudata(l, 1, "luaL_Text"));
                float height = luaL_checknumber(l, 2);
                foo->setFont(height);
                return 1;
            }
        },

        {
            "setAlignVertical", [](lua_State *l)
            {
                CRectangleText * foo = *static_cast<CRectangleText **>(luaL_checkudata(l, 1, "luaL_Text"));
                std::string align = luaL_checkstring(l, 2);
                if (align == "center")
                    foo->setFontAlign(EVerticalAlign::Center);
                else if (align == "top")
                    foo->setFontAlign(EVerticalAlign::Top);
                else if (align == "bottom")
                    foo->setFontAlign(EVerticalAlign::Bottom);
                //else
                // TODO: Обработка ситуации неправильного ввода
                return 1;
            }
        },

        {
            "setAlignHorizontal", [](lua_State *l)
            {
                CRectangleText * foo = *static_cast<CRectangleText **>(luaL_checkudata(l, 1, "luaL_Text"));
                std::string align = luaL_checkstring(l, 2);
                if (align == "center")
                    foo->setFontAlign(EHorizontalAlign::Center);
                else if (align == "left")
                    foo->setFontAlign(EHorizontalAlign::Left);
                else if (align == "right")
                    foo->setFontAlign(EHorizontalAlign::Right);
                //else
                // TODO: Обработка ситуации неправильного ввода
                return 1;
            }
        },

        "__gc", [](lua_State * l)
        {
            AbstractEntity * foo = *static_cast<CRectangleText **>(luaL_checkudata(l, 1, "luaL_Text"));
            CLuaManager::getInstance()->addObject<CRectangle>(foo);
            return 0;
        },

        { NULL, NULL }
    }; //luaL_Reg sFooRegs
    luaL_newmetatable(lua, "luaL_Text");
    luaL_setfuncs (lua, sFooRegs, 0);
    lua_pushvalue(lua, -1);
    lua_setfield(lua, -1, "__index");
    lua_setglobal(lua, "Text");
}

void CLuaManager::registerFolders()
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
                foo->mapOfParam[resName] = std::string(folder);
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

} // namespace Core


