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

#ifndef BASIC2DENTITY_H
#define BASIC2DENTITY_H

#include "core/objects/abstractentity.h"
#include "core/ogl/vertexbufferobject.h"
#include "core/ogl/vertexarrayobject.h"

namespace behemoth {

class CEventMouseClick;
class CApplication;
class DefaultScene;

/**
 * @brief Базовая сущность для генерирования и вывода пользовательского интерфейса.
 */
class CBasic2dEntity : public AbstractEntity
{
    friend class CBasicGUILayer;
    friend class CEntity2dFactory;
public:
    struct CVertex2D {
        glm::vec2 vertex;
        glm::vec2 uv;
        glm::vec3 color;
    }; // struct CVertex3D
    typedef std::vector<CVertex2D> CVertices2D;
    typedef std::vector<CBasic2dEntity*> CChilds2D;

    // AbstractEntity interface
public:
    virtual void paint() const override;
    virtual std::string getId() const override final;
    virtual void configure() override;

public:
    void setId(const std::string &id);

    // parent-childs
public:
    bool isRoot() const;
    virtual void setParent(CBasic2dEntity *m_parent);
    virtual CBasic2dEntity *getParent() const;
    virtual void addChild(CBasic2dEntity *child);
    virtual CBasic2dEntity *getChild(const std::string &id) final;
    virtual std::vector<CBasic2dEntity *> &getChilds() final;

    // gui stuff
public:
    /**
     * @brief Получить минимальную абсциссу ограничивающей поверхности.
     */
    virtual float getXMin() const = 0;
    /**
     * @brief Получить максимальную абсциссу ограничивающей поверхности.
     */
    virtual float getXMax() const = 0;
    /**
     * @brief Получить минимальную оординату ограничивающей поверхности.
     */
    virtual float getYMin() const = 0;
    /**
     * @brief Получить максимальную оординату ограничивающей поверхности.
     */
    virtual float getYMax() const = 0;

    /**
     * @brief Обработка клика
     */
    virtual void onClicked(const CEventMouseClick &event) = 0;

protected:
    CBasic2dEntity();
    explicit CBasic2dEntity(const std::string &id);
    virtual ~CBasic2dEntity();

    std::string m_id;                       /**< идентификатор. */
    CChilds2D m_childs;                     /**< Контейнер детей. */
    CBasic2dEntity *m_parent;               /**< Родитель. */

    CVertices2D m_vertices;                 /**< Контейнер вершин. */

    CVertexArrayObject m_vao;
    CVertexBufferObject m_vertexVBO;
}; // class Basic2dEntity

} // namespace behemoth

#endif // BASIC2DENTITY_H
