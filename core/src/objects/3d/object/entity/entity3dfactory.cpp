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

#include "entity3dfactory.h"

#include "core/lua/resourcemanager.h"

#include <fstream>
#include <iostream>

namespace bhm {

CEntity3dFactory *CEntity3dFactory::instance = nullptr;

class __CEntity3dFactoryImplDel {
public:
    explicit __CEntity3dFactoryImplDel(CEntity3dFactory *obj) : obj(obj) {}
    ~__CEntity3dFactoryImplDel() {delete obj;}
private:
    CEntity3dFactory *obj;
}; // class __CEntity3dFactoryImplDel

CEntity3dFactory *CEntity3dFactory::getInstance()
{
    if (!instance) {
        instance = new CEntity3dFactory;
        static __CEntity3dFactoryImplDel implDel(instance);
    }
    return instance;
}

CBasic3dEntity *CEntity3dFactory::loadEntity(const std::string &fileName)
{
    std::map<std::string, CBasic3dEntity*>::const_iterator it = m_entities.find(fileName);
    if (it != m_entities.end())
        return it->second;

    using namespace std;
    ifstream file;
    file.open(m_pathToMesh + fileName, ios::in | ios::binary);
    if (!file.good())
        return nullptr;

    struct CHeader {
        int32_t vertices;
        int32_t polygons;
    } meshHeader;
    struct CPolygon {
        unsigned short indOfVert[4]; // 4th - always 0
    };
    file.read(reinterpret_cast<char*>(&meshHeader), sizeof(CHeader));
    CBasic3dEntity::CVertices3d vertices(meshHeader.vertices);
    std::vector<CPolygon> polygons(meshHeader.polygons);
    file.read(reinterpret_cast<char*>(vertices.data()), sizeof(CBasic3dEntity::CVertex3d) * vertices.size());
    file.read(reinterpret_cast<char*>(polygons.data()), sizeof(CPolygon) * polygons.size());
    file.close();

    CBasic3dEntity *entity = new CBasic3dEntity(fileName);
    entity->m_vertices = vertices;
    for(CPolygon item : polygons) {
        entity->m_indexes.push_back({item.indOfVert[0], item.indOfVert[1], item.indOfVert[2]});
    }

    m_entities[fileName] = entity;

    return entity;
}

CEntity3dFactory::CEntity3dFactory() : m_entities(), m_pathToMesh(CResourceManager::getInstance()->getMeshFolder())
{
}

CEntity3dFactory::~CEntity3dFactory()
{
    for (auto item: m_entities)
        delete item.second;
}

} // namespace behemoth
