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

#include "basicnode.h"
#include "nodefactory.h"

#include "glm/ext.h"

#include "core/objects/3d/entity3dfactory.h"
#include "core/objects/3d/camerafactory.h"
#include "core/ogl/shaderfactory.h"
#include "core/lua/scene3dmanager.h"

namespace bhm {

CBasicNode::CBasicNode(const std::string &id) : m_id(id), m_orientation(), m_position(), m_entities()
{
}

CBasicNode::~CBasicNode()
{
    for (CBasicNode *node: m_childs)
        delete node;
}

void CBasicNode::setId(const std::string &id)
{
    m_id = id;
}

std::string CBasicNode::getId() const
{
    return m_id;
}

void CBasicNode::setPosition(const glm::vec3 &position)
{
    m_position = position;
}

glm::vec3 CBasicNode::getPosition() const
{
    return m_position;
}

void CBasicNode::rotate(float angle, const glm::vec3 &axis)
{

    m_orientation *= glm::angleAxis(angle, axis);
}

void CBasicNode::translate(const glm::vec3 &shift)
{
    m_position += shift;
}

glm::mat4 CBasicNode::getModelMatrix() const
{
    return glm::translate(glm::mat4(), m_position) * glm::toMat4(m_orientation);
}

void CBasicNode::addEntity3d(CBasic3dEntity *entity)
{
    m_entities.insert(entity);
    entity->setNode(this);
}

void CBasicNode::addEntity3d(const std::string &nameOfEntity)
{
    CBasic3dEntity *entity = CEntity3dFactory::getInstance()->loadEntity(nameOfEntity);
    if (entity) {
        m_entities.insert(entity);
        entity->setNode(this);
    }
}

CBasicNode::CEntities3d CBasicNode::getEntities() const
{
    return m_entities;
}

CBasic3dEntity *CBasicNode::getEntity(const std::string &nameOfEntity) const
{
    for (CBasic3dEntity *entity: m_entities) {
        if (entity->getId() == nameOfEntity)
            return entity;
    }
    return nullptr;
}

std::string CBasicNode::getNameOfFirstEntity() const
{
    if (m_entities.empty())
        return "";
    return (*m_entities.begin())->getId();
}

void CBasicNode::addChild(CBasicNode *node)
{
    m_childs.insert(node);
}

void CBasicNode::addChild(const std::string &nameOfNode)
{
    CBasicNode *node = CNodeFactory::getInstance()->getNode(nameOfNode);
    if (node)
        m_childs.insert(node);
}

CBasicNode::CChilds CBasicNode::getChilds() const
{
    return m_childs;
}

CBasicNode *CBasicNode::getChild(const std::string &nameOfNode) const
{
    for (CBasicNode *node: m_childs) {
        if (node->getId() == nameOfNode)
            return node;
    }
    return nullptr;
}

void CBasicNode::configureEntities()
{
    for (CBasic3dEntity *entity: m_entities) {
        entity->configure();
        CShader *shader = CShaderFactory::getInstance()->getShader("phong"); //! TODO: Вынести в CMaterial
        if (shader) {
            entity->m_vao.bind();
            shader->setAttribute("vertex", 3, 0, sizeof(CBasic3dEntity::CVertex3d));
            shader->setAttribute("normal", 3, 12, sizeof(CBasic3dEntity::CVertex3d));
    //        shader->setAttribute("uv", 2, 24, sizeof(CBasic3dEntity::CVertex3d));
            entity->m_vao.disable();
        }
    }
    for (CBasicNode *child: m_childs)
        child->configureEntities();
}

bool CBasicNode::onUpdateEntities()
{
    for (CBasic3dEntity *entity: m_entities)
        CScene3dManager::getInstance()->onUpdate(entity);
    for (CBasicNode *child: m_childs)
        child->onUpdateEntities();
    return true; // TODO: как тут быть?
}

void CBasicNode::paintEntities()
{
    for (CBasic3dEntity *entity: m_entities) {
        static AbstractCamera *cam = CCameraFactory::getInstance()->getActiveCamera();
        CShader *shader = CShaderFactory::getInstance()->getShader("phong"); //! TODO: Вынести в CMaterial
        if (cam && shader) {
            glm::mat4 mm = getModelMatrix();
            shader->setUniform("normal_matrix", cam->getNormalMatrix(mm));
            shader->setUniform("modelview_matrix", mm * cam->getViewMatrix());
            entity->paint();
        }
    }
    for (CBasicNode *child: m_childs)
        child->paintEntities();
}

bool CBasicNode::operator <(const CBasicNode &other) const
{
    return m_id < other.m_id;
}

} // namespace behemoth
