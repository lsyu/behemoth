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

#ifndef ALGOSTRING_H
#define ALGOSTRING_H

#include <vector>
#include <map>
#include <string>

/**
 * @brief Пространство имен обеспечивает доступ к алгоритмам со строками.
 */
namespace Algorithm {

/**
 * @brief Алгоритмы над строками.
 */
class Str
{
public:
    /**
     * @brief Разбить строку на подстроки, используя символ - разделитель @a delim.
     * @param s входная строка.
     * @param delim символ-разделитель.
     * @return полученный вектор строк.
     */
    static std::vector<std::string> split(const std::string &s, char delim);

    static std::vector<int> lengthOfSubstrings(const std::vector<std::string> &vecStr);

    /**
     * @brief Удалить пробелы из строки.
     * @param str строка.
     */
    static void spaceRemove(std::string &str);

    /**
     * @brief Разбить строку на подстроки, используя символ - разделитель @a delim и удалить пробелы.
     * @param s строка.
     * @param delim символ-разделитель.
     * @return полученный вектор строк.
     */
    static std::vector<std::string> splitAndSpaceRemove(const std::string &s, char delim);

    /**
     * @brief Преобразовать строку к целому.
     * @param s Входная строка.
     */
    static int strToInt(const std::string &s);

    /**
     * @brief Преобразовать целое к строке.
     * @param number целое число.
     */
    static std::string intToString(int numer);
    static std::string intToString(uint number);
    static std::string intToHexString(uint number);

    static std::string getFile(const std::string &fileName);

private:
    Str() {}
    static void split(const std::string &s, char delim,
                                           std::vector<std::string> &elems);
}; //class Str

} // namespace Algorithm

#endif /*ALGOSTING_H*/
