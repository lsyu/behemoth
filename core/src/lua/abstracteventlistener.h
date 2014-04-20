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

#ifndef ABSTRACTEVENTLISTENER_H
#define ABSTRACTEVENTLISTENER_H

#include <string>

namespace bhm {

class AbstractEntity;

/**
 * @brief Интерфейс слушателя событий.
 */
class AbstractEventListener
{
public:
    AbstractEventListener() {}
    virtual ~AbstractEventListener() {}

    /**
     * @brief Выполнить onClick из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    virtual bool onClick(AbstractEntity *entity) = 0;
    /**
     * @brief Выполнить onPressed из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    virtual bool onPressed(AbstractEntity *entity) = 0;
    /**
     * @brief Выполнить onReleased из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    virtual bool onReleased(AbstractEntity *entity) = 0;
    /**
     * @brief Выполнить onUpdate из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    virtual bool onUpdate(AbstractEntity *entity) = 0;
protected:
    /**
     * @brief Выполнить действие action из скрипта в lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    virtual bool executeAction(AbstractEntity *entity, const std::string &action) = 0;
}; // class AbstractEventListener

}// namespace behemoth

#endif // ABSTRACTEVENTLISTENER_H
