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

#include "nodefactory.h"
#include "core/lua/scene3dmanager.h"

namespace bhm {

CNodeFactory *CNodeFactory::instance = nullptr;
CBasicNode *CNodeFactory::m_rootNode = nullptr;

class __CNodeFactoryImplDel {
public:
    explicit __CNodeFactoryImplDel(CNodeFactory *obj) : obj(obj) {}
    ~__CNodeFactoryImplDel() {delete obj;}
private:
    CNodeFactory *obj;
}; // class __CEntity3dFactoryImplDel

CNodeFactory *CNodeFactory::getInstance()
{
    if (!instance) {
        instance = new CNodeFactory;
        static __CNodeFactoryImplDel delHelper(instance);
    }
    return instance;
}

CBasicNode *CNodeFactory::getNode(const std::string &name)
{
    std::map<std::string, CBasicNode*>::iterator it = m_nodes.find(name);
    if (it != m_nodes.end())
        return it->second;

    CBasicNode *node = new CBasicNode(name);
    if (m_nodes.empty())
        m_rootNode = node;
    m_nodes[name] = node;
    return node;
}

CBasicNode *CNodeFactory::getRootNode() const
{
    return m_rootNode;
}

CBasicNode *CNodeFactory::loadScene3d(const std::string fileName)
{
    if (!CScene3dManager::getInstance()->m_nodes.empty()) {
        // TODO: Что делать, если второй раз загружает?
        return m_rootNode;
    }
    if (!CScene3dManager::getInstance()->readScene3d(fileName))
        return nullptr;
    for(CBasicNode *node: CScene3dManager::getInstance()->m_nodes) {
        m_nodes[node->getId()] = node;
        if (!m_rootNode)
            m_rootNode = node;
    }
    return m_rootNode;
}

CNodeFactory::CNodeFactory() : m_nodes()
{
}

CNodeFactory::~CNodeFactory()
{
    if (m_rootNode)
        delete m_rootNode;
}

} // namespacebehemoth
