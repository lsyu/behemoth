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

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "object3d.h"

namespace behemoth {

class CObjectFactory
{
public:
    using CObjects3d = std::vector<CObject3d*>;

    static CObjectFactory *getInstance();
    /**
     * @brief загрузить сцену из файла.
     * @param fileName имя файла (директория должна содержаться в ресурсах)
     * @return Корневой элемент графического интерфейса.
     * @note имя необходимо указывать вместе с расширением!
     * @note в случае невозможности загрузки метод возвращает nullptr!
     */
    CObjects3d loadScene3d(const std::string &fileName);
private:
    CObjectFactory();
    ~CObjectFactory();
    CObjectFactory(const CObjectFactory &);
    CObjectFactory &operator =(const CObjectFactory &);

    static CObjectFactory *instance;
    CObjects3d m_objects;   /**< Контейнер объектов. */

    friend class __CObjectFactoryImplDel;
}; // class CObjectFactory

} // namespae behemoth

#endif // OBJECTFACTORY_H
