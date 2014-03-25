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

#include "entity2dfactory.h"
#include "core/lua/guimanager.h"

namespace behemoth {

CEntity2dFactory *CEntity2dFactory::instance = nullptr;

class __CEntity2dFactoryImplDel {
public:
    explicit __CEntity2dFactoryImplDel(CEntity2dFactory *obj) : obj(obj) {}
    ~__CEntity2dFactoryImplDel() {delete obj;}
private:
    CEntity2dFactory *obj;
}; // class __CEntity2dFactoryImplDel

CEntity2dFactory *CEntity2dFactory::getInstance()
{
    if (!instance) {
        instance = new CEntity2dFactory;
        static __CEntity2dFactoryImplDel implDel(instance);
    }
    return instance;
}

CBasic2dEntity *CEntity2dFactory::loadGUI(const std::string &fileName)
{
    if (!CGUIManager::getInstance()->readGui(fileName))
        return nullptr;
    if (CGUIManager::getInstance()->m_objects.empty())
        return nullptr;
    m_entities[fileName] = CGUIManager::getInstance()->m_objects.back();
    return CGUIManager::getInstance()->m_objects.back();
}

std::vector<CBasic2dEntity *> &CEntity2dFactory::getEntities4Event()
{
    return m_entities4Event;
}

CEntity2dFactory::CEntity2dFactory() : m_entities(), m_entities4Event()
{
}

CEntity2dFactory::~CEntity2dFactory()
{
    for (auto item: m_entities)
        delete item.second;
}

} // namespace behemoth
