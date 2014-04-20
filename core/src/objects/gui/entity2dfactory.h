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

#ifndef ENTITY2DFACTORY_H
#define ENTITY2DFACTORY_H

#include "basic2dentity.h"
#include "rectangle.h"
#include "rectangletext.h"

#include <string>
#include <map>

namespace bhm {

/**
 * @brief The Фабрика загрузки двумерных сущностей сущностей.
 * @note Сущности генерируются и удаляются здесь!
 */
class CEntity2dFactory
{
public:
    static CEntity2dFactory *getInstance();

    /**
     * @brief загрузить ui файл.
     * @param fileName имя файла (директория должна содержаться в ресурсах)
     * @return Корневой элемент графического интерфейса.
     * @note имя необходимо указывать вместе с расширением!
     * @note в случае невозможности загрузки метод возвращает nullptr!
     */
    CBasic2dEntity *loadGUI(const std::string &fileName);

    std::vector<CBasic2dEntity*> &getEntities4Event();

private:
    CEntity2dFactory();
    CEntity2dFactory(const CEntity2dFactory &);
    CEntity2dFactory &operator=(const CEntity2dFactory &);
    ~CEntity2dFactory();

    static CEntity2dFactory *instance;
    std::map<std::string, CBasic2dEntity*> m_entities;  /**< Контейнер сущностей. */

    std::vector<CBasic2dEntity*> m_entities4Event;   /**< Сущности, для которых выполнилось
                                                      * действие.
                                                      */

    friend class __CEntity2dFactoryImplDel;
}; // class CEntity2DFactory

} // namespace behemoth

#endif // ENTITY2DFACTORY_H
