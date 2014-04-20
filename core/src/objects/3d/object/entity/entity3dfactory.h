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

#ifndef ENTITY3DFACTORY_H
#define ENTITY3DFACTORY_H

#include "basic3dentity.h"
#include <map>

namespace bhm {

/**
 * @brief The Фабрика загрузки трехмерных сущностей.
 * @note Сущности генерируются и удаляются здесь!
 */
class CEntity3dFactory
{
public:
    static CEntity3dFactory *getInstance();

    /**
     * @brief loadEntity загрузить сущность из файла.
     * @param fileName имя файла (директория должна содержаться в ресурсах)
     * @return загруженная сущность
     * @note имя необходимо указывать вместе с расширением!
     * @note в случае невозможности загрузки метод возвращает nullptr!
     */
    CBasic3dEntity *loadEntity(const std::string &fileName);

private:
    CEntity3dFactory();
    CEntity3dFactory(const CEntity3dFactory &);
    CEntity3dFactory &operator=(const CEntity3dFactory &);
    ~CEntity3dFactory();

    static CEntity3dFactory *instance;
    std::map<std::string, CBasic3dEntity*> m_entities;  /**< Контейнер сущностей. */
    std::string m_pathToMesh;                           /**< Путь до ресурсов с mesh'ами. */

    friend class __CEntity3dFactoryImplDel;
}; // class CEntity3dFactory

} // namespace behemoth

#endif // ENTITY3DFACTORY_H
