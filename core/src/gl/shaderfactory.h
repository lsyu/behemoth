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

#ifndef SHADERFACTORY_H
#define SHADERFACTORY_H

#include <memory>
#include <string>
#include <map>

#include "core/ogl/shader.h"

namespace core {

/**
 * @brief Перечисления тип шейдера.
 */
enum class EShaderType : bool {
    VertexShader,    /**< Вершинный шейдер */
    FragmentShader    /**< Фрагментный шейдер */
}; // enum ShaderType

/**
 * @brief Фабрика получения шейдеров
 */
class CShaderFactory
{
public:
    /**
     * @brief Получить экземпляр фабрики шейдеров.
     */
    static CShaderFactory *getInstance();
    /**
     * @brief Получить шейдер по имени.
     * @param name имя шейдера
     * @note В случае, если шейдер невозможно получить, вернется nullptr.
     * @note bind/disable выполняются автоматически!
     */
    CShader *getShader(const std::string &name);
private:
    CShaderFactory();
    ~CShaderFactory();
    CShaderFactory(const CShaderFactory&);
    CShaderFactory &operator=(const CShaderFactory&);

    /**
     * @brief Подготовка шейдера. (Компилирование, линковка, проверка на корректность)
     * @param shader шейдер
     * @param vertShaderName Название файла вершинного шейдера.
     * @param fragmentShaderName Название файла фрагментного шейдера.
     * @return true если шейдер готов к работе, false в противном случае.
     * @note Шейдер должен находиться в каталоге, указанном в файле конфигурации.
     */
    bool prepareShader(CShader *shader, const std::string &vertShaderName, const std::string &fragmentShaderName);
    /** @brief Создание шейдера.
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
   bool makeShader(CShader *shader, EShaderType type, const char *source, int *sizes);
   /**
    * @brief Добавить шейдер к шейдерной программе.
    * @param type тип шейдера (вершинный или фрагментный).
    */
   void appendShader(CShader *shader, EShaderType type);
   /**
    * @brief Проверить состояние компиляции шейдера.
    * @param shader Шейдер (вершинный/фрагментный) для проверки.
    * @return true в случае, если шейдерная программа успешно прошела этап компиляции.
    * @note В случае провала вершинный, фрагментный шейдер, а также шейдерная программа удаляются.
    */
   bool checkCompileShaderStatus(CShader *program, uint shader);
   /**
    * @brief Проверить состояние линковки шейдерной программы.
    * @return true если шейдер уcпешно прошел этап линковки.
    * @note В случае провала вершинный, фрагментный шейдер, а также шейдерная программа удаляются.
    */
   bool checkLinkStatus(CShader *shader);
   /**
    * @brief Проверить валидность шейдера.
    * @return true если шейдер вылидный.
    * @note В случае провала вершинный, фрагментный шейдер, а также шейдерная программа удаляются.
    */
   bool checkValidateStatus(CShader *shader);
   /**
    * @brief Обработать ошибку при создании шейдерной программы.
    * @param shader шейдер или шейдерная программа.
    */
   void handleError(CShader *program, uint shader);
   /**
    * @brief При необходимости выполнить disable активного шейдера и bind нового шейдера.
    */
   CShader *changeActiveShader(CShader *newShader);

    static CShaderFactory *instance;
    std::string prefix;
    std::map< std::string, std::shared_ptr<CShader> > shaders;
    CShader *activeShader;

    friend class __CShaderFactoryImplDel;
}; // class ShaderFactory

} // namespace Core

#endif // SHADERFACTORY_H
