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
#include <stdexcept>

#include "glm/glm.h"

/**
 * @brief Перечисления тип шейдера.
 */
enum class ShaderType : bool {
    VertexShader,    /**< Вершинный шейдер */
    FragmentShader    /**< Фрагментный шейдер */
}; // enum ShaderType

/**
 * @brief Содержит все необходимое для работы с шейдерными программами GLSL 1.2
 */
class Shader
{
public:
    /**
     * @brief Конструктор по-умолчанию.
     *
     * Перед началом работы с шейдером необходимо его подготовить к работе!
     * @sa prepareShader
     */
    Shader();
    /**
     * @brief Конструктор, компилирующий вершинный и фрагментный шейдер и присоединяющий их к
     * шейдерной программе.
     * @param vertShaderName имя файла вершинного шейдера.
     * @param fragmentShaderName имя файла фрагментного шейдера.
     * @note Необходимо указывать только название файла, путь до директории с шейдерами должен
     * должен быть указан в файле конфигурации core.conf
     * @sa prepareShader, Core::ResourceManager
     */
    Shader(const std::string &vertShaderName, const std::string &fragmentShaderName);

    /**
     * @brief Подготовка шейдера. (Компилирование, линковка, проверка на корректность)
     * @param vertShaderName Название файла вершинного шейдера.
     * @param fragmentShaderName Название файла фрагментного шейдера.
     * @return true если шейдер готов к работе, false в противном случае.
     * @note Шейдер должен находиться в каталоге, указанном в файле конфигурации.
     */
    bool prepareShader(const std::string &vertShaderName, const std::string &fragmentShaderName);

    /**
     * @brief Метод, компилирующий вершинный и фрагментный шейдер и присоединяющий их к
     * шейдерной программе.
     * @param vertShaderName имя файла вершинного шейдера.
     * @param fragmentShaderName имя файла фрагментного шейдера.
     * @note Необходимо указывать только название файла, путь до директории с шейдерами должен
     * должен быть указан в файле конфигурации core.conf
     * @sa Core::ResourceManager
     */
    virtual ~Shader();

    /**
     * @brief Проверить состояние шейдера.
     * @return true если шейдер готов к работе.
     */
    bool isInit() const;

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
     * @brief Установить атрибут в шейдер.
     * @param nameOfParam название параметра в шейдере.
     * @param numOfComponent количество компонентов в данных.
     * @param stride "разрыв" до следующих данных.
     * @param ptr смещение до первого элемента.
     * @param type тип данных.
     * @param normalized нужно ли норализовать данные.
      @throw ShaderException в случае, если такого названия нет среди attribute переменных.
     */
    void setAttribute(const std::string &nameOfParam, int numOfComponents, int stride, const void *ptr,
                      uint type, bool normalized = false);

    /**
     * @brief Установить значение attribute.
     * @param nameOfParam название в шейдере.
     * @param value значение.
     * @throw ShaderException в случае, если такого названия нет среди attribute переменных.
     */
    void setAttribute(const std::string &nameOfParam, float value);
    /**
     * @brief Установить вектор attribute.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди attribute переменных.
     */
    void setAttribute(const std::string &nameOfParam, const glm::vec2 &vec);
    /**
     * @brief Установить вектор attribute.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди attribute переменных.
     */
    void setAttribute(const std::string &nameOfParam, const glm::vec3 &vec);
    /**
     * @brief Установить вектор attribute.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди attribute переменных.
     */
    void setAttribute(const std::string &nameOfParam, const glm::vec4 &vec);

    /**
     * @brief Установить значение uniform.
     * @param nameOfParam название в шейдере.
     * @param value значение.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, int value);

    /**
     * @brief Установить значение uniform.
     * @param nameOfParam название в шейдере.
     * @param value значение.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, float value);

    /**
     * @brief Установить вектор uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, const glm::vec2 &vec);
    /**
     * @brief Установить вектор uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, const glm::vec3 &vec);
    /**
     * @brief Установить вектор uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, const glm::vec4 &vec);
    /**
     * @brief Установить матрицу uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, const glm::mat2 &mat);
    /**
     * @brief Установить матрицу uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, const glm::mat3 &mat);
    /**
     * @brief Установить матрицу uniform.
     * @param nameOfParam название параметра в шейдере.
     * @param vec вектор.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    void setUniform(const std::string &nameOfParam, const glm::mat4 &mat);

    /**
     * @brief Найти адрес attribute переменной в шейдере.
     * @param nameOfParam название параметра в шейдере.
     * @return дескриптор адреса.
     * @throw ShaderException в случае, если такого названия нет среди attribute переменных.
     */
    uint makeAttributeLocation(const std::string &nameOfParam);

private:
    /**
     * @brief Создание шейдера.
     *
     * Включает:
     * - создание шейдера (glCreateShader).
     * - задание исходного кода шейдера (glShaderSource).
     * - компиляция шейдера (glCompileShader).
     * @n
     * Если хотя бы один из этих шагов не выполняется, шейдер не может быть использован!
     *
     * @param type Тип - вершинный или фрагментный.
     * @param source исходный код шейдера.
     * @param sizes длинны строк шейдера.
     * @return true - если все операции успешны, false в противном случае.
     */
    bool makeShader(ShaderType type, const char *source, int *size);

    /**
     * @brief Добавить шейдер к шейдерной программе.
     * @param type тип шейдера (вершинный или фрагментный).
     */
    void appendShader(ShaderType type);

    /**
     * @brief Проверить состояние компиляции шейдера.
     * @param shader Шейдер (вершинный/фрагментный) для проверки.
     * @return true в случае, если шейдерная программа успешно прошела этап компиляции.
     * @note В случае провала вершинный, фрагментный шейдер, а также шейдерная программа удаляются.
     */
    bool checkCompileShaderStatus(uint shader);

    /**
     * @brief Проверить состояние линковки шейдерной программы.
     * @return true если шейдер уcпешно прошел этап линковки.
     * @note В случае провала вершинный, фрагментный шейдер, а также шейдерная программа удаляются.
     */
    bool checkLinkStatus();

    /**
     * @brief Проверить валидность шейдера.
     * @return true если шейдер вылидный.
     * @note В случае провала вершинный, фрагментный шейдер, а также шейдерная программа удаляются.
     */
    bool checkValidateStatus();

    /**
     * @brief Обработать ошибку при создании шейдерной программы.
     * @param shader шейдер или шейдерная программа.
     */
    void handleError(uint shader);

    /**
     * @brief Найти адрес uniform переменной в шейдере.
     * @param nameOfParam название параметра в шейдере.
     * @return дескриптор адреса.
     * @throw ShaderException в случае, если такого названия нет среди uniform переменных.
     */
    int makeUniformLocation(const std::string &nameOfParam);


    std::map<std::string, int> cacheAttribute;
    std::map<std::string, int> cacheUniform;
    uint vertexShader;
    uint fragmentShader;
    uint shaderProgram;
    bool init;
}; // class Shader

/**
 * @brief Исключения при работе с шейдерами.
 */
class ShaderException : public std::runtime_error
{
public:
    ShaderException(const std::string &text) : std::runtime_error(text) {}
}; // class ShaderException

#endif // SHADER_H
