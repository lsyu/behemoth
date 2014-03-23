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

#include "entityfactory.h"

#include "core/lua/resourcemanager.h"

#include <fstream>
#include <iostream>

namespace core {

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
    std::map<std::string, CBasic3dEntity*>::const_iterator it = mEntities.find(fileName);
    if (it != mEntities.end())
        return it->second;

    using namespace std;
    ifstream file;
    file.open(prefix + fileName, ios::in | ios::binary);
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
    CBasic3dEntity::CVertices vertices(meshHeader.vertices);
    std::vector<CPolygon> polygons(meshHeader.polygons);
    file.read(reinterpret_cast<char*>(vertices.data()), sizeof(CBasic3dEntity::CVertex) * vertices.size());
    file.read(reinterpret_cast<char*>(polygons.data()), sizeof(CPolygon) * polygons.size());
    file.close();

    CBasic3dEntity *entity = new CBasic3dEntity(fileName);
    entity->mVertices = vertices;
    for(CPolygon item : polygons) {
        entity->mIndexes.push_back({item.indOfVert[0], item.indOfVert[1], item.indOfVert[2]});
    }

    mEntities[fileName] = entity;

    return entity;
}

CEntityFactory::CEntityFactory() : mEntities(), prefix(CResourceManager::getInstance()->getMeshFolder())
{
}

CEntityFactory::~CEntityFactory()
{
    for (auto item: mEntities)
        delete item.second;
}

} // namespace core
