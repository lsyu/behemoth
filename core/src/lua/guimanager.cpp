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
#include "core/objects/gui/rectangle.h"
#include "core/objects/gui/rectangletext.h"

#include "core/lua/resourcemanager.h"

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
    std::string scriptPath = CResourceManager::getInstance()->getGUIFolder() + fileName;
    bool ret = !luaL_dofile(lua, scriptPath.c_str());
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
    luaL_dostring(lua, "glm = {}");
    registerVec2();
    registerVec3();
    registerBorder();
    registerGradient();
    registerText();
    registerRectangle();
}

void CGUIManager::registerVec2()
{
    CLuaWrapper<glm::vec2> v(lua, "vec2");
    v.setNameSpace("glm");
    v.addConstructor<float, float>();
    v.AddProperty(float)("x", &glm::vec2::x);
    v.AddProperty(float)("y", &glm::vec2::y);
    v.addDestructor();
    v.complete(false);
}

void CGUIManager::registerVec3()
{
    CLuaWrapper<glm::vec3> v(lua, "vec3");
    v.setNameSpace("glm");
    v.addConstructor<float, float, float>();
    v.AddProperty(float)("x", &glm::vec3::x);
    v.AddProperty(float)("y", &glm::vec3::y);
    v.AddProperty(float)("z", &glm::vec3::z);
    v.addDestructor();
    v.complete(false);
}

void CGUIManager::registerBorder()
{
    CLuaWrapper<CBorderRadius> r(lua, "radius");
    r.addConstructor();
    r.AddProperty(float)("radius", &CBorderRadius::getRadius, &CBorderRadius::setRadius);
    r.AddProperty(float)("bottomLeft", &CBorderRadius::getBottomLeft, &CBorderRadius::setBottomLeft);
    r.AddProperty(float)("topLeft", &CBorderRadius::getTopLeft, &CBorderRadius::setTopLeft);
    r.AddProperty(float)("topRight", &CBorderRadius::getTopRight, &CBorderRadius::setTopRight);
    r.AddProperty(float)("bottomRight", &CBorderRadius::getBottomRight, &CBorderRadius::setBottomRight);
    r.addDestructor();
    r.complete(true);

    CLuaWrapper<CBorder> b(lua, "border");
    b.addConstructor();
    b.AddProperty(float)("width", &CBorder::width);
    b.AddProperty(glm::vec3)("color", &CBorder::color);
    b.addDestructor();
    b.complete(true);
}

void CGUIManager::registerGradient()
{
    CLuaWrapper<CGradient> g(lua, "gradient");
    g.addConstructor();
    g.AddProperty(glm::vec3)("bottomLeft", &CGradient::bottomLeft);
    g.AddProperty(glm::vec3)("topLeft", &CGradient::topLeft);
    g.AddProperty(glm::vec3)("topRight", &CGradient::topRight);
    g.AddProperty(glm::vec3)("bottomRight", &CGradient::bottomRight);
    g.addDestructor();
    g.complete(true);
}

void CGUIManager::registerText()
{
    CLuaWrapper<CRectangleText> t(lua, "text");
    t.addConstructor();
    t.AddProperty(std::string)("text", &CRectangleText::getText, &CRectangleText::setText);
    t.AddProperty(std::string)("font", &CRectangleText::getFontName, &CRectangleText::setFont);
    t.AddProperty(float)("height", &CRectangleText::getFontHeight, &CRectangleText::setFont);
    t.AddProperty(std::string)("alignVertical", &CRectangleText::getVericalAlignStr, &CRectangleText::setVerticalAlign);
    t.AddProperty(std::string)("alignHorizontal", &CRectangleText::getHorizontalAlignStr, &CRectangleText::setHorizontalAlign);
    t.complete(true);
}

void CGUIManager::registerRectangle()
{
    CLuaWrapper<CRectangle> r(lua, "rectangle");
    r.addConstructor<std::string>();
    r.AddProperty(std::string)("id", &CRectangle::getId, &CRectangle::setId);
    r.AddProperty(float)("x", &CRectangle::getXMin, &CRectangle::setX);
    r.AddProperty(float)("y", &CRectangle::getYMin, &CRectangle::setY);
    r.AddProperty(float)("width", &CRectangle::getWidth, &CRectangle::setWidth);
    r.AddProperty(float)("height", &CRectangle::getHeight, &CRectangle::setHeight);
    r.AddProperty(glm::vec3)("color", &CRectangle::getColor, &CRectangle::setColor);
    r.AddProperty(float)("alpha", &CRectangle::getAlpha, &CRectangle::setAlpha);
    r.AddProperty(std::string)("texture", &CRectangle::getTexture, &CRectangle::setTexture);
    r.AddProperty(CBorderRadius)("radius", &CRectangle::getRadius, &CRectangle::setRadius);
    r.AddProperty(CBorder)("border", &CRectangle::getBorder, &CRectangle::setBorder);
    r.AddProperty(CGradient)("gradient", &CRectangle::getGradient, &CRectangle::setGradient);
    r.AddProperty(CRectangleText)("text", &CRectangle::getText, &CRectangle::setText);


    r.addProperty({"addChild", [](lua_State *l) {
                       CRectangle * foo = __CLuaWrapper::checkUserData<CRectangle>(l, 1);
                       CBasic2dEntity * bar = *static_cast<CBasic2dEntity **>(lua_touserdata(l, 2));
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
    r.complete(true);
}

core::CBasic2dEntity *CGUIManager::getObject(const std::string &id)
{
    std::vector< std::shared_ptr<core::CBasic2dEntity> >::iterator it
            = std::find_if(objects.begin(), objects.end(),
            [&id](const std::shared_ptr<core::CBasic2dEntity> &obj)
            {
                return obj->getId() == id;
            });
    return it != objects.end() ? static_cast<core::CBasic2dEntity*>(&(*it->get())) : nullptr;
}

core::CBasic2dEntity *CGUIManager::getObject(int num)
{
    if (num < 0 || num >= static_cast<int>(objects.size()))
        return nullptr;
    return objects[num].get();
}

CBasic2dEntity *CGUIManager::getRootObject()
{
    return objects.empty() ? nullptr : dynamic_cast<CBasic2dEntity*>(objects.back().get());
}

const std::vector< std::shared_ptr<core::CBasic2dEntity> >& CGUIManager::getObjects() const
{
    return objects;
}

template<class T>
void CGUIManager::addObject(CBasic2dEntity *t)
{
    objects.push_back(std::shared_ptr<CBasic2dEntity>(dynamic_cast<T*>(t)));
}

bool CGUIManager::executeAction(CBasic2dEntity *entity, const std::string &action)
{
    lua_getglobal(lua, "ui");
    if (lua_istable(lua, -1))
    {
        lua_getfield(lua, -1, entity->getId().c_str());
        if (lua_istable(lua, -1)) {
            lua_getfield(lua, -1, action.c_str());
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

bool CGUIManager::onClick(CBasic2dEntity *entity)
{
    return executeAction(entity, "onClick");
}

bool CGUIManager::onPressed(CBasic2dEntity *entity)
{
    return executeAction(entity, "onPressed");
}

bool CGUIManager::onReleased(CBasic2dEntity *entity)
{
    return executeAction(entity, "onReleased");
}

} // namespace Core


