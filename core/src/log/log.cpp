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

#include "log.h"
#include <iostream>

using namespace std;

namespace Core {

std::shared_ptr<Log> Log::instance = nullptr;

Log::Log()
{
}

Log::~Log()
{
    //! TODO: Подумать над уничтожением!
}

Log* Log::getInstance()
{
    if (!instance)
        instance = std::shared_ptr<Log>(new Log());
    return instance.get();
}

void Log::test(const char *message) const
{
    cout << message;
}

void Log::test(const string &message) const
{
    cout << message;
}

} // namespace Core
