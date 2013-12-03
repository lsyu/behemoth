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

/**
 * @mainpage Документация проекта пока что безымянного движка.
 *
 * @section WTOC Содержание
 * - @ref Description
 * - @ref License
 * @n
 * @n
 * @n
 *
 * @section Description Описание
 * Данный проект базируется на нескольких очень классных проектах:
 * - glm - матрицы
 * - gli - изображения
 * - freeglut - инициализация контекста OpenGL, создание окна, перефирийные устройства.
 * - lua - скрипты
 * @n
 * @n
 * @n
 *
 * @section License Лицензия
 * Если честно, я хз! Я Везде пока что втыкаю GPL.
 * @n
 * @n
 * @n
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <string>
#include <vector>
#include <set>

#include "glm/glm.h"

namespace core {

class AbstractEvent;
class AbstractScene;
class __CApplicationImplDel;

/**
 * @brief Глубина цвета.
 */
enum class EColorDepth: unsigned short int {
    _8 = 8,     /**< 8 */
    _16 = 16,   /**< 16 */
    _32 = 32,   /**< 32 */
    _64 = 64    /**< 64 */
}; // enum ColorDepth

/**
 * @brief Главный класс Вашего приложения
 *
 * Архитектура - singleton.
 * Производит инициализацию приложения, получает контекст OpenGl
 * и много чего еще полезного делает.
 *
 */
class CApplication
{
public:
    friend class AbstractScene;
    friend class __CApplicationImplDel;

    /**
     * @brief Получить экземпляр приложения.
     * @return экземпляр приложения.
     */
    static CApplication* getInstance();

    /**
     * @brief Инициализация ресурсов приложения.
     * @sa exec
     */
    void initialize(int &argc, char *argv[]);
    /**
     * @brief Запустить главный цикл приложения.
     *
     * Перед запуском главного цикла необходимо проинициализировать все необходимые приложению
     * ресурсы, вызвав @a init
     * @n
     * Пример запуска главного приложения:
     * @code
     * #include "core/application.h"
     * #include "core/defaultscene.h"
     * int main(int argc, char *argv[])
     * {
     *     using namespace core;
     *     CApplication *app = CApplication::getInstance();
     *     app->initialize(argc, argv);
     *     app->setWindowTitle("Test");
     *     app->setFullScreen(false);
     *     app->setSize(glm::ivec2(800, 600));
     *     app->setColorDepth(EColorDepth::_32);
     *
     *     DefaultScene scene;
     *     app->setScene(&scene);
     *
     *     app->exec();
     *
     *     return 0;
     * }
     * @endcode
     * @sa initialize
     */
    void exec();

    /**
     * @brief Закрыть приложение.
     */
    void close();

    /**
     * @brief Установить обработчика рисования.
     * @param painter обработчик рисования.
     */
    void setScene(core::AbstractScene *scene);

    /**
     * @brief Установить заголовок окна.
     */
    void setWindowTitle(const std::string &title);
    /**
     * @brief Получить заголовок окна.
     */
    std::string getWindowTitle() const;

    /**
     * @brief Установить параметр экрана.
     * @param fullScreen true - полный экран, false - оконный режим.
     */
    void setFullScreen(bool fullScreen);

    /**
     * @brief Получить параметр экрана
     * @return true - полный экран, false - оконный режим.
     */
    bool isFullScreen() const;

    /**
     * @brief Установить позицию окна.
     */
    void setPosition(const glm::ivec2 &position);

    /**
     * @brief Получить позицию окна.
     */
    glm::ivec2 getPosition() const;

    /**
     * @brief Установть размеры окна.
     */
    void setSize(const glm::ivec2 &size);

    /**
     * @brief Получить размеры окна.
     */
    glm::ivec2 getSize() const;

    /**
     * @brief Получить размеры дисплея.
     */
    glm::ivec2 getDisplaySize() const;

    /**
     * @brief Установить глубину цвета.
     */
    void setColorDepth(EColorDepth depth);

    /**
     * @brief Получить глубину цвета.
     */
    EColorDepth getColorDepth() const;

    /**
     * @brief Получить промежуток времени, потраченный на последний кадр(в секундах).
     */
    float getSecondOfLastFrame() const;

    /**
     * @brief Конвертирование координат из абсолютных в относительные в пр-ве изображения.
     */
    static glm::vec2 getRelativeCoordinate(const glm::ivec2 &absoluteCoordinate);
    /**
     * @brief Конвертирование координат из абсолютных в относительные в пр-ве изображения.
     */
    static glm::vec2 getRelativeCoordinate(int x, int y);

private:
    CApplication();
    ~CApplication();
    CApplication(const CApplication&);
    CApplication &operator=(const CApplication&);

    /**
     * @brief Обработчик нажатия клавиши.
     */
    static void key(unsigned char key, int x, int y);
    /**
     * @brief Обработчик клика мыши.
     */
    static void mouse(int button, int state, int x, int y);
    /**
     * @brief Обработчик отрисовки.
     */
    static void display();
    /**
     * @brief Обработчик без события
     */
    static void idle();

    static CApplication *instance;

    std::string title;          /**< Заголовок окна. */
    bool fullScreen;            /**< Полный ли экран. */
    glm::ivec2 position;        /**< положение верхнего левого угла окна. */
    glm::ivec2 size;            /**< Размеры окна(Высота, ширина). */
    glm::ivec2 displaySize;     /**< Размеры экрана. */
    EColorDepth depth;          /**< Глубина цвета. */
    AbstractScene *painter;     /**< Сцена для рисования. */
    int windowId;               /**< Идентификатор окна. */
    float secOfLastFrame;       /**< Время визуализации последнего кадра. */
}; // class Application

} // namespace Core

#endif /*APPLICATION_H*/
