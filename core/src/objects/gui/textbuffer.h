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

#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <vector>

namespace core {

/**
 * @brief Структура, содержащая буфер текста для рендера и вспомогательную информацию
 */
class CTextBuffer {
public:
    CTextBuffer();
    std::vector<unsigned char> buffer;  /**< Буффер текста */
    unsigned int width;                 /**< Длина текста */
    unsigned int height;                /**< Высота текста */
    bool isLoad;                        /**< Успешно ли загружен текст */
}; // struct CBuffer

} // namespace core

#endif // TEXTBUFFER_H
