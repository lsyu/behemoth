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

#include "scene3dmanager.h"
#include "luawrapper.h"

#include "core/objects/3d/entity3dfactory.h"
#include "core/objects/3d/camerafactory.h"
#include "core/objects/3d/lightfactory.h"
#include "core/objects/3d/object3d.h"

#include "core/lua/resourcemanager.h"

#include "glm/glm.h"

#include <iostream>

namespace behemoth {

CScene3dManager *CScene3dManager::instance = nullptr;

class __CScene3dManagerImplDel {
public:
    explicit __CScene3dManagerImplDel(CScene3dManager *manager) : manager(manager) {}
    ~__CScene3dManagerImplDel() {delete manager;}
private:
    CScene3dManager *manager;
};

CScene3dManager *CScene3dManager::getInstance()
{
    if (!instance) {
        instance = new CScene3dManager;
        static __CScene3dManagerImplDel delHelper(instance);
    }
    return instance;
}

CScene3dManager::CScene3dManager() : AbstractEventListener(), CBasicLuaManager()
{
    if (m_lua)
        registerScene3d();
}

CScene3dManager::~CScene3dManager()
{
}

bool CScene3dManager::onClick(AbstractEntity *entity)
{
    return executeAction(entity, "onClick");
}

bool CScene3dManager::onPressed(AbstractEntity *entity)
{
    return executeAction(entity, "onPressed");
}

bool CScene3dManager::onReleased(AbstractEntity *entity)
{
    return executeAction(entity, "onReleased");
}

bool CScene3dManager::onUpdate(AbstractEntity *entity)
{
    return executeAction(entity, "onUpdate");
}

bool CScene3dManager::executeAction(AbstractEntity *entity, const std::string &action)
{
    lua_getglobal(m_lua, "bgm");
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
                std::string log(lua_tostring(m_lua, -1));
                std::cout << log;
                lua_pop(m_lua, 2);
                return false;
            }
        }
        lua_pop(m_lua, 2);
        return true;
    }
    return false;
}

bool CScene3dManager::readScene3d(const std::string &fileName)
{
    if (!m_lua)
        return false;
    std::string scriptPath = CResourceManager::getInstance()->getScene3dFolder() + fileName;
    bool ret = !luaL_dofile(m_lua, scriptPath.c_str());
    if(!ret) {
        // TODO: Залогировать!
        std::string log(lua_tostring(m_lua, -1));
        std::cout << log;
    }
    return ret;

}

void CScene3dManager::addObject(CObject3d *object)
{
    m_objects.push_back(object);
}

void CScene3dManager::registerScene3d()
{
    luaL_dostring(m_lua, "bgm = {}");
    registerObject();
    registerCamera();
    registerLight();
}

void CScene3dManager::registerObject()
{
    CLuaWrapper<CObject3d> o(m_lua, "object");
    o.setNameSpace("bgm");
    o.addConstructor<std::string>();
    o.AddProperty(std::string)("id", &CObject3d::getId, &CObject3d::setId);
    o.AddProperty(std::string)("entity", &CObject3d::getEntity, &CObject3d::setEntity);
    o.AddProperty(glm::vec3)("position", &CObject3d::getPosition, &CObject3d::setPosition);
    o.addProperty({"rotate", [](lua_State *l) {
                       CObject3d *t =  __CLuaWrapper::checkUserData<CObject3d>(l, 1);
                       float angle = __CLuaWrapper::checkType<float>(l, 2);
                       glm::vec3 *axis = __CLuaWrapper::checkUserData<glm::vec3>(l, 3);
                       t->rotate(angle, *axis);
                       return 1;
                   }
                  });
    o.addProperty({"sync", [](lua_State *l) {
                       CObject3d *t = __CLuaWrapper::checkUserData<CObject3d>(l, 1);
                       CScene3dManager::getInstance()->addObject(t);
                       return 1;
                   }
                  });
    o.complete(true);
}

void CScene3dManager::registerLight()
{

}

void CScene3dManager::registerCamera()
{

}

} // namespace behemoth
