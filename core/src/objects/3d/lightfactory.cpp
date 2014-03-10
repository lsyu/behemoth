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

#include "lightfactory.h"

namespace core {

CLightFactory *CLightFactory::instance = nullptr;

class __CLightFactoryImplDel {
public:
    explicit __CLightFactoryImplDel(CLightFactory *obj) : obj(obj) {}
    ~__CLightFactoryImplDel() {delete obj;}
private:
    CLightFactory *obj;
}; // class __CLightFactoryImplDel

CLightFactory *CLightFactory::getInstance()
{
    if (instance) {
        instance = new CLightFactory;
        static __CLightFactoryImplDel impDel(instance);
    }
    return instance;
}

CPointLight *CLightFactory::getPointLight(const std::string &name) const
{
    std::map<std::pair<std::string, ELightType>, AbstractLight*>::const_iterator it
            = lights.find(std::pair<std::string, ELightType>(name, ELightType::point));
    if(it != lights.end())
        return static_cast<CPointLight*>(it->second);
    return nullptr;
}

CDirectionLight *CLightFactory::getDirectionLight(const std::string &name) const
{
     std::map<std::pair<std::string, ELightType>, AbstractLight*>::const_iterator it
             = lights.find(std::pair<std::string, ELightType>(name, ELightType::direction));
     if(it != lights.end())
         return static_cast<CDirectionLight*>(it->second);
     return nullptr;
}

void CLightFactory::makeLight(const std::string &name, ELightType type)
{
    AbstractLight *light = nullptr;
    if (type == ELightType::direction)
        light = new CDirectionLight;
    else if (type == ELightType::point)
        light = new CPointLight;
    if (light)
        lights[std::pair<std::string, ELightType>(name, type)] = light;
}

CLightFactory::CLightFactory() : lights()
{
}

CLightFactory::~CLightFactory()
{
    for (auto item : lights)
        delete item.second;
}

} // namespace core
