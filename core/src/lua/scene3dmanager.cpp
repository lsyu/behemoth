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

#include "core/lua/resourcemanager.h"

#include "glm/glm.h"

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
}

CScene3dManager::~CScene3dManager()
{
}

bool CScene3dManager::onClick(AbstractEntity *entity)
{

}

bool CScene3dManager::onPressed(AbstractEntity *entity)
{

}

bool CScene3dManager::onReleased(AbstractEntity *entity)
{

}

bool CScene3dManager::executeAction(AbstractEntity *entity, const std::string &action)
{

}

bool CScene3dManager::readScene3d(const std::string &fileName)
{

}

} // namespace behemoth
