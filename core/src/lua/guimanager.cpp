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

#include "guimanager.h"
#include "luawrapper.h"

#include "core/objects/gui/entity2dfactory.h"
#include "core/lua/resourcemanager.h"

#include "glm/glm.h"

#include <algorithm>
#include <iostream>

namespace behemoth {

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
    }
    return instance;
}

CGUIManager::CGUIManager() : AbstractEventListener(), CBasicLuaManager(), m_objects()
{
    if (m_lua)
        registerUI();
}

CGUIManager::~CGUIManager()
{
}

bool CGUIManager::readGui(const std::string &fileName)
{
    if (!m_lua)
        return false;
    std::string scriptPath = CResourceManager::getInstance()->getGUIFolder() + fileName;
    bool ret = !luaL_dofile(m_lua, scriptPath.c_str());
    if(!ret) {
        // TODO: Залогировать!
        std::string log(lua_tostring(m_lua, -1));
        std::cout << log;
    }
    return ret;
}

void CGUIManager::registerUI()
{
    luaL_dostring(m_lua, "ui = {}");
    luaL_dostring(m_lua, "glm = {}");
    registerVec2();
    registerVec3();
    registerBorder();
    registerGradient();
    registerText();
    registerRectangle();
}

void CGUIManager::registerVec2()
{
    CLuaWrapper<glm::vec2> v(m_lua, "vec2");
    v.setNameSpace("glm");
    v.addConstructor<float, float>();
    v.AddProperty(float)("x", &glm::vec2::x);
    v.AddProperty(float)("y", &glm::vec2::y);
    v.addDestructor();
    v.complete(false);
}

void CGUIManager::registerVec3()
{
    CLuaWrapper<glm::vec3> v(m_lua, "vec3");
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
    CLuaWrapper<CBorderRadius> r(m_lua, "radius");
    r.addConstructor();
    r.AddProperty(float)("radius", &CBorderRadius::getRadius, &CBorderRadius::setRadius);
    r.AddProperty(float)("bottomLeft", &CBorderRadius::getBottomLeft, &CBorderRadius::setBottomLeft);
    r.AddProperty(float)("topLeft", &CBorderRadius::getTopLeft, &CBorderRadius::setTopLeft);
    r.AddProperty(float)("topRight", &CBorderRadius::getTopRight, &CBorderRadius::setTopRight);
    r.AddProperty(float)("bottomRight", &CBorderRadius::getBottomRight, &CBorderRadius::setBottomRight);
    r.addDestructor();
    r.complete(true);

    CLuaWrapper<CBorder> b(m_lua, "border");
    b.addConstructor();
    b.AddProperty(float)("width", &CBorder::width);
    b.AddProperty(glm::vec3)("color", &CBorder::color);
    b.addDestructor();
    b.complete(true);
}

void CGUIManager::registerGradient()
{
    CLuaWrapper<CGradient> g(m_lua, "gradient");
    g.addConstructor();
    g.AddProperty(glm::vec3)("bottomLeft", &CGradient::m_bottomLeft);
    g.AddProperty(glm::vec3)("topLeft", &CGradient::m_topLeft);
    g.AddProperty(glm::vec3)("topRight", &CGradient::m_topRight);
    g.AddProperty(glm::vec3)("bottomRight", &CGradient::m_bottomRight);
    g.addDestructor();
    g.complete(true);
}

void CGUIManager::registerText()
{
    CLuaWrapper<CRectangleText> t(m_lua, "text");
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
    CLuaWrapper<CRectangle> r(m_lua, "rectangle");
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
                       CGUIManager::getInstance()->addObject(t);
                       return 1;
                   }
                  });
    r.complete(true);
}

void CGUIManager::addObject(CBasic2dEntity *t)
{
    m_objects.push_back(t);
}

bool CGUIManager::onClick(AbstractEntity *entity)
{
    return executeAction(entity, "onClick");
}

bool CGUIManager::onPressed(AbstractEntity *entity)
{
    return executeAction(entity, "onPressed");
}

bool CGUIManager::onReleased(AbstractEntity *entity)
{
    return executeAction(entity, "onReleased");
}

bool CGUIManager::executeAction(AbstractEntity *entity, const std::string &action)
{
    lua_getglobal(m_lua, "ui");
    if (lua_istable(m_lua, -1))
    {
        lua_getfield(m_lua, -1, entity->getId().c_str());
        if (lua_istable(m_lua, -1)) {
            lua_getfield(m_lua, -1, action.c_str());
            if (!lua_isfunction(m_lua, -1)) {
                lua_pop(m_lua, 3);
                return false;
            }
            lua_getfield(m_lua, -3, entity->getId().c_str());
            if (lua_pcall(m_lua, 1, 0, 0)) {
                lua_pop(m_lua, 2);
                return false;
            }
        }
        lua_pop(m_lua, 2);
        return true;
    }
    return false;
}

} // namespace behemoth


