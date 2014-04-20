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

#include "camerafactory.h"

#include "perspectivecamera.h"
#include "orthocamera.h"

namespace bhm {

CCameraFactory *CCameraFactory::instance = nullptr;

class __CCameraFactoryImplDel {
public:
    explicit __CCameraFactoryImplDel(CCameraFactory *obj) : obj(obj) {}
    ~__CCameraFactoryImplDel() {delete obj;}
private:
    CCameraFactory *obj;
}; // class __CCameraFactoryImplDel

CCameraFactory *CCameraFactory::getInstance()
{
    if (!instance) {
        instance = new CCameraFactory;
        static __CCameraFactoryImplDel impDel(instance);
    }
    return instance;
}

AbstractCamera *CCameraFactory::getCamera(const std::string &name) const
{
    std::map<std::string, AbstractCamera*>::const_iterator it = m_cameras.find(name);
    if (it != m_cameras.end())
        return it->second;
    return nullptr;
}

AbstractCamera *CCameraFactory::getActiveCamera() const
{
    return m_activeCamera;
}

void CCameraFactory::setActiveCamera(AbstractCamera *activeCamera)
{
    m_activeCamera = activeCamera;
}

void CCameraFactory::makePerspectiveCamera(const std::string &name, float widthOfVieport, float heightOfVieportf, float fov, float nearPlane, float farPlane)
{
    if (m_cameras.find(name) == m_cameras.end())
        m_cameras[name] = new CPerspectiveCamera(widthOfVieport, heightOfVieportf, fov, nearPlane, farPlane);
}

void CCameraFactory::makeOrthoCamera(const std::string &name, float left, float right, float bottom, float top, float near, float far)
{
    if (m_cameras.find(name) == m_cameras.end())
        m_cameras[name] = new COrthoCamera(left, right, bottom, top, near, far);
}

CCameraFactory::CCameraFactory() : m_cameras(), m_activeCamera(nullptr)
{
}

CCameraFactory::~CCameraFactory()
{
    for (auto item: m_cameras)
        delete item.second;
}



} // namespace behemoth
