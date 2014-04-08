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

#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include "basicnode.h"
#include <string>
#include <map>

namespace behemoth {

/**
 * @brief Фабрика получения вершины графа сцены.
 */
class CNodeFactory
{
public:
    static CNodeFactory *getInstance();

    CBasicNode *addNode(const std::string &name);
    /**
     * @brief Получить корневой элемент графа сцены.
     * @note Если граф пустой, вернется nullptr.
     */
    CBasicNode *getRootNode() const;
    /**
     * @brief Получить элемент графа сцены по имени.
     * @note Если элемент отсутствует, вернется nullptr.
     */
    CBasicNode *getNode(const std::string &name) const;

private:
    CNodeFactory();
    ~CNodeFactory();
    CNodeFactory(const CNodeFactory &);
    CNodeFactory &operator =(const CNodeFactory &);

    static CNodeFactory *instance;
    static CBasicNode *m_rootNode;              /**< Корневой элемент. */
    std::map<std::string, CBasicNode*> m_nodes; /**< Узлы графа сцены. */

    friend class __CNodeFactoryImplDel;
}; // class CNodeFactory

} // namespace behemoth

#endif // NODEFACTORY_H
