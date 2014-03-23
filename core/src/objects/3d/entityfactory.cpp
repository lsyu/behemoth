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

#include "entityfactory.h"

#include "core/lua/resourcemanager.h"

#include <fstream>
#include <iostream>

namespace behemoth {

CEntityFactory *CEntityFactory::instance = nullptr;

class __CEntityFactoryImplDel {
public:
    explicit __CEntityFactoryImplDel(CEntityFactory *obj) : obj(obj) {}
    ~__CEntityFactoryImplDel() {delete obj;}
private:
    CEntityFactory *obj;
}; // class __CEntityFactoryImplDel

CEntityFactory *CEntityFactory::getInstance()
{
    if (!instance) {
        instance = new CEntityFactory;
        static __CEntityFactoryImplDel implDel(instance);
    }
    return instance;
}

CBasic3dEntity *CEntityFactory::loadEntity(const std::string &fileName)
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
    CBasic3dEntity::CVertices3D vertices(meshHeader.vertices);
    std::vector<CPolygon> polygons(meshHeader.polygons);
    file.read(reinterpret_cast<char*>(vertices.data()), sizeof(CBasic3dEntity::CVertex3D) * vertices.size());
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

CEntityFactory::CEntityFactory() : m_entities(), m_pathToMesh(CResourceManager::getInstance()->getMeshFolder())
{
}

CEntityFactory::~CEntityFactory()
{
    for (auto item: m_entities)
        delete item.second;
}

} // namespace behemoth
