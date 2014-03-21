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

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "basic3dentity.h"
#include <map>

namespace core {

/**
 * @brief The Фабрика загрузки трехмерных сущностей.
 */
class CEntityFactory
{
public:
    static CEntityFactory *getInstance();

    /**
     * @brief loadEntity загрузить сущность из файла.
     * @param fileName имя файла (директория должна содержаться в ресурсах)
     * @return загруженная сущность
     * @note имя необходимо указывать вместе с расширением!
     * @note в случае невозможности загрузки метод возвращает nullptr!
     */
    CBasic3dEntity *loadEntity(const std::string &fileName);

private:
    CEntityFactory();
    CEntityFactory(const CEntityFactory &);
    CEntityFactory &operator=(const CEntityFactory &);
    ~CEntityFactory();

    static CEntityFactory *instance;
    std::map<std::string, CBasic3dEntity*> mEntities;
    std::string prefix;

    friend class __CEntityFactoryImplDel;
}; // class CEntityFactory

} // namespace core

#endif // ENTITYFACTORY_H
