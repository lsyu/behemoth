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

#include "guimanager.h"
#include "luawrapper.h"

#include "core/objects/abstractentity.h"
#include "core/objects/2d/rectangle.h"
#include "core/objects/2d/rectangletext.h"

#include "core/manager/resourcemanager.h"

#include "glm/glm.h"

#include <algorithm>
#include <iostream>

namespace core {

CGUIManager *CGUIManager::instance = nullptr;

class __CGUIManagerImplDel {
public:
    explicit __CGUIManagerImplDel(CGUIManager *luaManager) : luaManager(luaManager) {}
    ~__CGUIManagerImplDel() {delete luaManager;}
private:
    CGUIManager *luaManager;
};

CGUIManager *CGUIManager::getInstance()
{
    if (!instance) {
        instance = new CGUIManager();
        static __CGUIManagerImplDel delHelper(instance);
        instance->init();
    }
    return instance;
}

CGUIManager::CGUIManager() : lua(nullptr), objects()
{
}

CGUIManager::~CGUIManager()
{
}

bool CGUIManager::readGui(const std::string &fileName)
{
    if (!lua)
        init();
    bool ret = !luaL_dofile(lua, fileName.c_str());
    if(!ret) {
        // TODO: Залогировать!
        std::string log(lua_tostring(lua, -1));
        std::cout << log;
    }
    close();
    return ret;
}

void CGUIManager::init()
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

void CGUIManager::close()
{
    if (lua) {
        if (!objects.empty())
            objects.back()->configure();
    }
}

void CGUIManager::registerUI()
{
    luaL_dostring(lua, "ui = {}");
    registerVec2();
    registerVec3();
    registerText();
    registerRectangle();
}

void CGUIManager::registerVec2()
{
    CLuaWrapper<glm::vec2> v(lua, "vec2");
    v.addConstructor<float, float>();
    v.addProperty<float, 1>("x", &glm::vec2::x);
    v.addProperty<float, 2>("y", &glm::vec2::y);
    v.addDestructor();
    v.complete();
}

void CGUIManager::registerVec3()
{
    CLuaWrapper<glm::vec3> v(lua, "vec3");
    v.addConstructor<float, float, float>();
    v.addProperty<float, 1>("x", &glm::vec3::x);
    v.addProperty<float, 2>("y", &glm::vec3::y);
    v.addProperty<float, 3>("z", &glm::vec3::z);
    v.addDestructor();
    v.complete();
}

void CGUIManager::registerRectangle()
{
    CLuaWrapper<CRectangle> r(lua, "rectangle");
    r.addConstructor<std::string>();
    r.addProperty<float, 1>("x", &CRectangle::getXMin, &CRectangle::setX);
    r.addProperty<float, 2>("y", &CRectangle::getYMin, &CRectangle::setY);
    r.addProperty<float, 3>("width", &CRectangle::getWidth, &CRectangle::setWidth);
    r.addProperty<float, 4>("height", &CRectangle::getHeight, &CRectangle::setHeight);
    r.addProperty<glm::vec3, 5>("color", &CRectangle::getColor, &CRectangle::setColor);
    r.addProperty<float, 6>("radiusOfA", &CRectangle::getRadiusOfA, &CRectangle::setRadiusOfA);
    r.addProperty<float, 7>("radiusOfB", &CRectangle::getRadiusOfB, &CRectangle::setRadiusOfB);
    r.addProperty<float, 8>("radiusOfC", &CRectangle::getRadiusOfC, &CRectangle::setRadiusOfC);
    r.addProperty<float, 9>("radiusOfD", &CRectangle::getRadiusOfD, &CRectangle::setRadiusOfD);
    r.addProperty<float, 10>("radius", &CRectangle::getRadius, &CRectangle::setRadius);
    r.addProperty<float, 11>("alpha", &CRectangle::getAlpha, &CRectangle::setAlpha);
    r.addProperty<std::string, 12>("texture", &CRectangle::getTexture, &CRectangle::setTexture);
    r.addProperty<float, 13>("borderWidth", &CRectangle::getBorderWidth, &CRectangle::setBorderWidth);
    r.addProperty<glm::vec3, 14>("borderColor", &CRectangle::getBorderColor, &CRectangle::setBorderColor);


    r.addProperty({"addChild", [](lua_State *l) {
                       CRectangle * foo = __CLuaWrapper::checkUserData<CRectangle>(l, 1);
                       AbstractEntity * bar = *static_cast<AbstractEntity **>(lua_touserdata(l, 2));
                       foo->addChild(bar);
                       return 1;
                   }
                  });
    r.addProperty({"sync", [](lua_State *l) {
                       CRectangle *t = __CLuaWrapper::checkUserData<CRectangle>(l, 1);
                       CGUIManager::getInstance()->addObject<CRectangle>(t);
                       return 1;
                   }
                  });
    r.complete();
}

void CGUIManager::registerText()
{
    CLuaWrapper<CRectangleText> t(lua, "text");
    t.addConstructor();
    t.addProperty<std::string, 1>("text", &CRectangleText::getText, &CRectangleText::setText);
    t.addProperty<std::string, 2>("font", &CRectangleText::getFontName, &CRectangleText::setFont);
    t.addProperty<float, 3>("height", &CRectangleText::getFontHeight, &CRectangleText::setFont);
    t.addProperty<std::string, 4>("alignVertical", &CRectangleText::getVericalAlignStr, &CRectangleText::setVerticalAlign);
    t.addProperty<std::string, 5>("alignHorizontal", &CRectangleText::getHorizontalAlignStr, &CRectangleText::setHorizontalAlign);
    t.addProperty({"sync", [](lua_State *l)
                   {

                       CRectangleText *t = __CLuaWrapper::checkUserData<CRectangleText>(l, 1);
                       CGUIManager::getInstance()->addObject<CRectangle>(t);
                       return 1;
                   }
                  });
    t.complete();
}

core::AbstractEntity *CGUIManager::getObject(const std::string &id)
{
    std::vector< std::shared_ptr<core::AbstractEntity> >::iterator it
            = std::find_if(objects.begin(), objects.end(),
            [&id](const std::shared_ptr<core::AbstractEntity> &obj)
            {
                return obj->getId() == id;
            });
    return it != objects.end() ? static_cast<core::AbstractEntity*>(&(*it->get())) : nullptr;
}

core::AbstractEntity *CGUIManager::getObject(int num)
{
    if (num < 0 || num >= static_cast<int>(objects.size()))
        return nullptr;
    return objects[num].get();
}

Basic2dEntity *CGUIManager::getRootObject()
{
    return dynamic_cast<Basic2dEntity*>(objects.back().get());
}

const std::vector< std::shared_ptr<core::AbstractEntity> >& CGUIManager::getObjects() const
{
    return objects;
}

template<class T>
void CGUIManager::addObject(AbstractEntity *t)
{
    objects.push_back(std::shared_ptr<AbstractEntity>(dynamic_cast<T*>(t)));
}

bool CGUIManager::runOnClickFor(AbstractEntity *entity)
{
    lua_getglobal(lua, "ui");
    if (lua_istable(lua, -1))
    {
        //lua_getfield(lua, -1, );
        lua_getfield(lua, -1, entity->getId().c_str());
        if (lua_istable(lua, -1)) {
            lua_getfield(lua, -1, "onClick");
            if (!lua_isfunction(lua, -1)) {
                lua_pop(lua, 3);
                return false;
            }
            lua_getfield(lua, -3, entity->getId().c_str());
            if (lua_pcall(lua, 1, 0, 0)) {
                lua_pop(lua, 2);
                return false;
            }
        }
        lua_pop(lua, 2);
        return true;
    }
    return false;
}

} // namespace Core


