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

#ifndef BASICLUAMANAGER_H
#define BASICLUAMANAGER_H

#include "lua/lua.h"

namespace bhm {

/**
 * @brief Базовый класс менеджера Lua.
 * @note Необходим, чтобы не беспокоиться о памяти, связанной с Lua.
 */
class CBasicLuaManager
{
public:
    /**
     * @brief Очистить стек Lua
     */
    void closeLua();

protected:
    CBasicLuaManager();
    virtual ~CBasicLuaManager();

private:
    CBasicLuaManager(const CBasicLuaManager &);
    CBasicLuaManager &operator =(const CBasicLuaManager &);

protected:
    static lua_State *m_lua;   /**< стек Lua. */
}; // class CBasicLuaManager

} // namespace behemoth

#endif // BASICLUAMANAGER_H
