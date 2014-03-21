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

#include "camerafactory.h"

#include "perspectivecamera.h"
#include "orthocamera.h"

namespace core {

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
    std::map<std::string, AbstractCamera*>::const_iterator it = mCameras.find(name);
    if (it != mCameras.end())
        return it->second;
    return nullptr;
}

AbstractCamera *CCameraFactory::getActiveCamera() const
{
    return mActiveCamera;
}

void CCameraFactory::setActiveCamera(AbstractCamera *activeCamera)
{
    mActiveCamera = activeCamera;
}

void CCameraFactory::makePerspectiveCamera(const std::string &name, float widthOfVieport, float heightOfVieportf, float fov, float nearPlane, float farPlane)
{
    if (mCameras.find(name) == mCameras.end())
        mCameras[name] = new CPerspectiveCamera(widthOfVieport, heightOfVieportf, fov, nearPlane, farPlane);
}

void CCameraFactory::makeOrthoCamera(const std::string &name, float left, float right, float bottom, float top, float near, float far)
{
    if (mCameras.find(name) == mCameras.end())
        mCameras[name] = new COrthoCamera(left, right, bottom, top, near, far);
}

CCameraFactory::CCameraFactory() : mCameras(), mActiveCamera(nullptr)
{
}

CCameraFactory::~CCameraFactory()
{
    for (auto item: mCameras)
        delete item.second;
}



} // namespace core
