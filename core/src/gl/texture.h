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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

#include "glm/glm.h"

namespace behemoth {

class CTexture
{
    friend class CTextureFactory;
public:
    unsigned int getId() const;
    glm::uvec2 getSize() const;
    std::string getFileName() const;

private:
    CTexture();
    CTexture(const CTexture &);
    CTexture &operator =(const CTexture &);
    ~CTexture();

    unsigned int m_id;          /**< Идентификатор загруженной текстуры. */
    glm::uvec2 m_size;         /**< Размер текстуры. */
    std::string m_fileName;  /**< Название файла, из которого загружена текстура. */
}; // class CTexture

class CTextureBuffer {
public:
    std::vector<unsigned char> m_buffer;  /**< Буффер текста */
    unsigned short int m_width;                  /**< Длина текста */
    unsigned short int m_height;                /**< Высота текста */
}; // struct CBuffer

} // namespace behemoth

#endif // TEXTURE_H
