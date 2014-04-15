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

#include "object3d.h"
#include "entity/entity3dfactory.h"
#include "node/nodefactory.h"

#include "core/ogl/ogl.h"
#include "core/ogl/shaderfactory.h"

#include "core/objects/3d/camerafactory.h"
#include "core/objects/3d/lightfactory.h"

#include "glm/ext.h"

behemoth::CObject3d::CObject3d(const std::string &name)
    : m_entity(nullptr),
      m_node(CNodeFactory::getInstance()->addNode(name))
{
}

behemoth::CObject3d::~CObject3d()
{
}

void behemoth::CObject3d::setPosition(const glm::vec3 &position)
{
    m_node->setPosition(position);
}

glm::vec3 behemoth::CObject3d::getPosition() const
{
    return m_node->getPosition();
}

void behemoth::CObject3d::setEntity(const std::string &entity)
{
    m_entity = CEntity3dFactory::getInstance()->loadEntity(entity);
}

std::string behemoth::CObject3d::getEntity() const
{
    if (m_entity)
        return m_entity->getId();
    return std::string();
}

void behemoth::CObject3d::configure()
{
    if (m_entity) {
        m_entity->configure();
        CShader *shader = CShaderFactory::getInstance()->getShader("phong"); //! TODO: Вынести в CMaterial
        m_entity->m_vao.bind();
        shader->setAttribute("vertex", 3, 0, sizeof(CBasic3dEntity::CVertex3d));
        shader->setAttribute("normal", 3, 12, sizeof(CBasic3dEntity::CVertex3d));
//        shader->setAttribute("uv", 2, 24, sizeof(CBasic3dEntity::CVertex3d));
        m_entity->m_vao.disable();
    }
}

void behemoth::CObject3d::paint()
{
    if (m_entity && m_node) {
        static AbstractCamera *cam = CCameraFactory::getInstance()->getActiveCamera();
        static CPointLight *light = CLightFactory::getInstance()->getLight("test");
        if (cam) {
            cam->rotatePosition(1, 1, 0, 0); //! TODO: Декларативно!
            m_node->rotate(1);
            CShader *shader = CShaderFactory::getInstance()->getShader("phong"); //! TODO: Вынести в CMaterial
            if (shader) {
                shader->setUniform("modelview_matrix", m_node->getModelMatrix() * cam->getViewMatrix());
                shader->setUniform("projection_matrix", cam->getProjectionMatrix());
                shader->setUniform("normal_matrix", cam->getNormalMatrix(m_node->getModelMatrix()));
                shader->setUniform("light_position", light->getPosition());
                shader->setUniform("eye_position", cam->getEye());
                m_entity->paint();
            }
        }
    }
}
