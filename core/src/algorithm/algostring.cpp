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

#include "algostring.h"
#include <sstream>
#include <strstream>
#include <algorithm>
#include <memory>
#include <fstream>

namespace Algorithm {

void Str::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
        elems.push_back(item);
}

std::vector<std::string> Str::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<int> Str::lengthOfSubstrings(const std::vector<std::string> &vecStr)
{
    std::vector<int> ret(vecStr.size());
    for (int i = 0, n = vecStr.size(); i < n; ++i)
        ret.push_back(vecStr[i].size());
    return ret;
}

void Str::spaceRemove(std::string &str)
{
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

std::vector<std::string> Str::splitAndSpaceRemove(const std::string &s, char delim)
{
    std::vector<std::string> elems = split(s, delim);
    for(std::vector<std::string>::iterator it = elems.begin(), end = elems.end();
        it != end; ++it)
        spaceRemove(*it);
    return elems;
}

int Str::strToInt(const std::string &s)
{
    int ret;
    std::istringstream(s) >> ret;
    return ret;
}

std::string Str::intToString(int number)
{
    std::stringstream convert;
    convert << number;
    return convert.str();
}

std::string Str::intToString(uint number)
{
    std::stringstream convert;
    convert << number;
    return convert.str();
}

std::string Str::intToHexString(uint number)
{
    std::stringstream convert;
    convert << std::hex << number;
    return convert.str();
}

std::string Str::getFile(const std::string &fileName)
{
    std::string ret((std::istreambuf_iterator<char>(*(std::auto_ptr<std::ifstream>(
            new std::ifstream(fileName))).get())), std::istreambuf_iterator<char>());
    return ret;
}

} // namespace Algorithm
