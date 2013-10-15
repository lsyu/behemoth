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

#ifndef LOG_H
#define LOG_H

#include <memory>
#include <string>

namespace Core {

/**
 * @brief Логирование системы.
 *
 * @todo Замутить логер!
 */
class Log
{
public:
    /**
     * @brief Получить экземпляр логера.
     *
     * Не следует удалять указатель на Log при его получении,
     * так как система сама следит за освобождением памяти.
     */
    static Log* getInstance();

    /**
     * @brief Деструктор.
     */
    virtual ~Log();

    void test(const char *message) const;
    void test(const std::string &message) const;

private:
    /**
     * @brief Конструктор по-умолчанию.
     */
    Log();
    /**
     * @brief Конструктор копирования.
     */
    Log(const Log& other);
    /**
     * @brief Оператор присваивания.
     */
    Log& operator=(const Log& other);

    static std::shared_ptr<Log> instance;
}; // class Log

} // namespace Core

#endif // LOG_H
