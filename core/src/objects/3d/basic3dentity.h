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

#ifndef BASIC3DENTITY_H
#define BASIC3DENTITY_H

#include "core/objects/abstractentity.h"
#include "core/ogl/vertexbufferobject.h"
#include "core/ogl/vertexarrayobject.h"
#include <array>

namespace core {

/**
 * @brief Базовая сущность трехмерного объекта
 */
class CBasic3dEntity : public AbstractEntity
{
    friend class CEntityFactory;
    friend class CBasicScene3dLayer; //! TODO: УБРАТЬ!!!
public:
    typedef std::vector<glm::vec3> CCoords;
    typedef std::vector< std::array<unsigned short int, 3> > CIndexes;
    typedef std::vector<glm::vec3> CNormals;
    typedef std::vector<glm::vec2> CUVCoords;
    typedef std::vector<CBasic3dEntity*> CChilds3D;

    // AbstractEntity interface
public:
    virtual void paint() const override;
    virtual std::string getId() const override;
protected:
    virtual void configure() override;

    // parent-childs
public:
    virtual bool isRoot() const final;
    virtual void setParent(CBasic3dEntity *parent) final;
    virtual CBasic3dEntity *getParent() const final;
    virtual void addChild(CBasic3dEntity *child) final;
    virtual CBasic3dEntity *getChild(const std::string &id) final;
    virtual std::vector<CBasic3dEntity *> &getChilds() final;

protected:
    explicit CBasic3dEntity(const std::string &id);
    virtual ~CBasic3dEntity();

    std::string mId;            /**< идентификатор */
    CChilds3D mChilds;          /**< список детей */
    CBasic3dEntity *mParent;    /**< Родитель сущности. */

    CCoords mVertixes;  /**< список координат вершин */
    CUVCoords mUVs;     /**< список текстурных координат */
    CIndexes mIndexes;  /**< список индексов полигонов */
    CNormals mNormals;  /**< список нормалей полигонов */

    CVertexArrayObject mVAO;
    CVertexBufferObject mVertexVBO;
    CVertexBufferObject mIndexVBO;
}; // class CBasic3dEntity

} // namespace core

#endif // BASIC3DENTITY_H
