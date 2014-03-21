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

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>
#include <map>

#include "glm/glm.h"

namespace core {

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
     * @brief Установить атрибут в шейдер.
     * @param nameOfParam название параметра в шейдере.
     * @param numOfComponent количество компонентов в данных.
     * @param stride "разрыв" до следующих данных.
     * @param ptr смещение до первого элемента.
     * @param type тип данных.
     * @param normalized нужно ли норализовать данные.
     */
    void setAttribute(const std::string &nameOfParam, int numOfComponents, int stride, const void *ptr,
                      uint type, bool normalized = false);

    /**
     * @brief Установить значение attribute.
     * @param nameOfParam название в шейдере.
     * @param value значение.
     */
    void setAttribute(const std::string &nameOfParam, float value);
    /**
     * @brief Установить вектор attribute.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setAttribute(const std::string &nameOfParam, const glm::vec2 &vec);
    /**
     * @brief Установить вектор attribute.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setAttribute(const std::string &nameOfParam, const glm::vec3 &vec);
    /**
     * @brief Установить вектор attribute.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     */
    void setAttribute(const std::string &nameOfParam, const glm::vec4 &vec);

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

} // namespace core

#endif // SHADER_H
