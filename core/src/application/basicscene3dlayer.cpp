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

#include "basicscene3dlayer.h"

#include "core/ogl/ogl.h"
#include "core/ogl/shaderfactory.h"
#include "core/objects/3d/entity3dfactory.h"
#include "core/objects/3d/camerafactory.h"
#include "core/objects/3d/lightfactory.h"
#include "core/objects/3d/object3dfactory.h"
#include "core/lua/scene3dmanager.h"

namespace behemoth {

CBasicScene3dLayer::CBasicScene3dLayer(const std::string &fileName) : AbstractLayer(), m_objects(), m_fileName(fileName)
{
}

CBasicScene3dLayer::~CBasicScene3dLayer()
{
}

void CBasicScene3dLayer::prepareGL()
{
    CCameraFactory::getInstance()->makePerspectiveCamera("test", 640, 480);
    AbstractCamera *cam = CCameraFactory::getInstance()->getCamera("test");
    cam->lookAt(glm::vec3(7, 7, 5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
    CCameraFactory::getInstance()->setActiveCamera(cam);

    CLightFactory::getInstance()->makeLight("test", ELightType::point);
    CPointLight *light = CLightFactory::getInstance()->getLight("test", ELightType::point);
    light->setPosition(7, 7, 5);

    m_objects = CObjectFactory::getInstance()->loadScene3d(m_fileName);
    for(CObject3d *obj: m_objects) {
        obj->configure();
    }
}

bool CBasicScene3dLayer::updateGL()
{
    for(CObject3d *obj : m_objects) {
        if (!CScene3dManager::getInstance()->onUpdate(obj->getEntity3d()))
            return false;
    }
    return true;
}

void CBasicScene3dLayer::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_BLEND);

    for(CObject3d *obj : m_objects) {
        obj->paint();
    }
}

} // namespace behemoth
