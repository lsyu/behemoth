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

#include "objectfactory.h"
#include "core/lua/scene3dmanager.h"

namespace behemoth {

CObjectFactory *CObjectFactory::instance = nullptr;

class __CObjectFactoryImplDel {
public:
    explicit __CObjectFactoryImplDel(CObjectFactory *obj) : obj(obj) {}
    ~__CObjectFactoryImplDel() {delete obj;}
private:
    CObjectFactory *obj;
}; // class __CCameraFactoryImplDel

CObjectFactory *CObjectFactory::getInstance()
{
    if (!instance) {
        instance = new CObjectFactory;
        static __CObjectFactoryImplDel implDel(instance);
    }
    return instance;
}

CObjectFactory::CObjects3d CObjectFactory::loadScene3d(const std::string &fileName)
{
    if (!CScene3dManager::getInstance()->m_objects.empty()) {
        // TODO: Что делать, если второй раз загружает?
        return m_objects;
    }
    if (!CScene3dManager::getInstance()->readScene3d(fileName))
        return CObjects3d();
    if (CScene3dManager::getInstance()->m_objects.empty())
        return CObjects3d();
    m_objects = CScene3dManager::getInstance()->m_objects;
    return m_objects;
}

CObjectFactory::CObjectFactory()
{
}

CObjectFactory::~CObjectFactory()
{
    for (CObject3d *obj: m_objects) {
        delete obj;
    }
}

} // namespace behemoth
