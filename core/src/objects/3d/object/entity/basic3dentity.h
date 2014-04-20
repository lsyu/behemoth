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

#ifndef BASIC3DENTITY_H
#define BASIC3DENTITY_H

#include "core/objects/abstractentity.h"
#include "core/ogl/vertexbufferobject.h"
#include "core/ogl/vertexarrayobject.h"

#include <array>

namespace bhm {

class CBasicNode;

/**
 * @brief Базовая сущность трехмерного объекта
 */
class CBasic3dEntity : public AbstractEntity
{
    friend class CEntity3dFactory;
    friend class CBasicNode;
public:
    struct CVertex3d {
        glm::vec3 vertex;
        glm::vec3 normal;
        glm::vec2 uv;
    }; // struct CVertex3D
    typedef std::vector<CVertex3d> CVertices3d;
    typedef std::vector< std::array<unsigned short int, 3> > CIndexes;
    typedef std::vector<CBasic3dEntity*> CChilds3D;

    // AbstractEntity interface
public:
    virtual void paint() const override;
    virtual std::string getId() const override final;
    virtual void configure() override;

    // parent-childs
public:
    virtual bool isRoot() const final;
    virtual void setParent(CBasic3dEntity *parent) final;
    virtual CBasic3dEntity *getParent() const final;
    virtual void addChild(CBasic3dEntity *child) final;
    virtual CBasic3dEntity *getChild(const std::string &id) final;
    virtual std::vector<CBasic3dEntity *> &getChilds() final;

    CBasicNode *getNode() const;

    bool operator <(const CBasic3dEntity &other) const;
protected:
    explicit CBasic3dEntity(const std::string &id);
    virtual ~CBasic3dEntity();


    /**
     * @brief Установить идентификатор данной сущности.
     */
    void setId(const std::string &id);
    void setNode(CBasicNode *node);

    std::string m_id;            /**< Идентификатор */
    CChilds3D m_childs;          /**< Список детей */
    CBasic3dEntity *m_parent;    /**< Родитель сущности. */
    CBasicNode *m_node;          /**< Узел, к которому привязана сущность. */

    CVertices3d m_vertices; /**< список атрибутов вершины. */
    CIndexes m_indexes;     /**< список индексов вершин. */

    CVertexArrayObject m_vao;
    CVertexBufferObject m_vertexVBO;
    CVertexBufferObject m_indexVBO;
}; // class CBasic3dEntity

} // namespace behemoth

#endif // BASIC3DENTITY_H
