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

#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include <vector>
#include "glm/glm.h"

namespace behemoth {

/**
 * @brief Перечисления типа массива данных.
 */
enum class EArrayType : bool {
    Data,    /**< Данные */
    Index    /**< Индексы */
}; // enum EArrayType

/**
 * @brief Адаптер для работы с VBO.
 *
 * Подробно о VBO смотри на opengl.org
 */
class CVertexBufferObject
{
public:
    /**
     * @brief Конструктор по-умолчанию.
     *
     * Перед началом работы с VBO, его нужно сгенерировать!
     * @sa genBuffer
     */
    CVertexBufferObject(EArrayType type = EArrayType::Data);
    virtual ~CVertexBufferObject();
    /**
     * @brief Генерирование VBO.
     */
    void genBuffer();
    /**
     * @brief Сделать VBO активным.
     */
    void bind() const;
    /**
     * @brief Сделать VBO неактивным.
     **/
    void disable() const;

    /**
     * @brief Заполнить VBO данными.
     */
    template <typename T>
    void setData(const std::vector<T> *buffer) const {
        setData(buffer->data(), buffer->capacity()*sizeof(T));
    }
    /**
     * @brief Заполнить VBO данными.
     */
    void setData(const void *data, size_t sizeOfData) const;
private:
    uint m_vbo;         /**< Идентификатор vbo. */
    EArrayType m_type;  /**< тип vbo. */

}; // class VertexBufferObject

} // namespace behemoth

#endif // VERTEXBUFFEROBJECT_H
