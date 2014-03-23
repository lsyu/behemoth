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

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>
#include <map>

#include "glm/glm.h"

namespace behemoth {

/**
 * @brief Содержит все необходимое для работы с шейдерными программами GLSL 1.2
 */
class CShader
{
public:
    friend class CShaderFactory;

    /**
     * @brief Очистка ресурсов
     */
    ~CShader();
    /**
     * @brief Установить attribute.
     *
     * Например,имеем структуру
     * @code
     * struct CVertex {
     *     glm::vec3 vertex; // 3 of float
     *     glm::vec3 normal; // 3 of float
     *     glm::vec2 uv;     // 2 of float
     * }; // struct CVertex
     * @endcode
     * Чтобы установить attribute-переменные, необходимо выполнить:
     * @code
     * shader->setAttribute("vertex", 3, 0,  sizeof(CVertex)); // begin of struct
     * shader->setAttribute("normal", 3, 12, sizeof(CVertex)); // sizeof(glm::vec3)
     * shader->setAttribute("uv",     2, 24, sizeof(CVertex)); // sizeof(glm::vec3) + sizeof(glm::vec3)
     * @endcode
     *
     * @todo Тип элемента.
     * @param nameOfParam название параметра в шейдере.
     * @param numberOfElement количество элементов заданного типа.
     * @param offsetFromBeginToElements смещение от начала структуры до элементов заданного типа.
     * @param sizeOfStruct размер всей структуры.
     * @return индекс размещения в шейдере.
     */
    unsigned int setAttribute(const std::string &nameOfParam, int numberOfElement, size_t offsetFromBeginToElements, size_t sizeOfStruct);
    void setAttribute(unsigned int location, int numberOfElement, size_t offsetFromBeginToElements, size_t sizeOfStruct);

    /**
     * @brief Установить значение uniform.
     * @param nameOfParam название в шейдере.
     * @param value значение.
     */
    void setUniform(const std::string &nameOfParam, int value);

    /**
     * @brief Установить значение uniform.
     * @param nameOfParam название в шейдере.
     * @param value значение.
     */
    void setUniform(const std::string &nameOfParam, float value);

    /**
     * @brief Установить вектор uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setUniform(const std::string &nameOfParam, const glm::vec2 &vec);
    /**
     * @brief Установить вектор uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setUniform(const std::string &nameOfParam, const glm::vec3 &vec);
    /**
     * @brief Установить вектор uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setUniform(const std::string &nameOfParam, const glm::vec4 &vec);
    /**
     * @brief Установить матрицу uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setUniform(const std::string &nameOfParam, const glm::mat2 &mat);
    /**
     * @brief Установить матрицу uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setUniform(const std::string &nameOfParam, const glm::mat3 &mat);
    /**
     * @brief Установить матрицу uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setUniform(const std::string &nameOfParam, const glm::mat4 &mat);

private:
    CShader(const std::string &id);
    /**
     * @brief Сделать шейдерную программу активной.
     *
     * Читай glUseProgram
     */
    void bind() const;

    /**
     * @brief Задизаблить шейдерную программу.
     *
     * Читай glUseProgram(0);
     */
    void disable() const;
    /**
     * @brief Найти адрес uniform переменной в шейдере.
     * @param nameOfParam название параметра в шейдере.
     * @return дескриптор адреса (-1 в случае ошибки).
     */
    int makeUniformLocation(const std::string &nameOfParam);
    /**
     * @brief Найти адрес attribute переменной в шейдере.
     * @param nameOfParam название параметра в шейдере.
     * @return дескриптор адреса.
     */
    uint makeAttributeLocation(const std::string &nameOfParam);

    std::map<std::string, int> cacheAttribute;
    std::map<std::string, int> cacheUniform;
    uint vertexShader;
    uint fragmentShader;
    uint shaderProgram;
    std::string id;
}; // class Shader

} // namespace behemoth

#endif // SHADER_H
