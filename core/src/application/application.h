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
 * Данный проект базируется на нескольких очень классных проектах (думаю, со временем он еще
 * поабрастет зависимостями):
 * - glm - матрицы
 * - gli - изображения
 * - Allegro 5 - инициализация контекста OpenGL, создание окна, перефирийные устройства.
 * - Lua 5.2.2 - скрипты
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

struct ALLEGRO_DISPLAY;
struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRO_TIMER;
union ALLEGRO_EVENT;

namespace core {

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
     */
    void initialize(int &argc, char *argv[]);

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
     * @brief Установить глубину цвета.
     */
    void setColorDepth(EColorDepth depth);

    /**
     * @brief Получить глубину цвета.
     */
    EColorDepth getColorDepth() const;

    /**
     * @brief Установить шаг таймера.
     */
    void setTimerStep(double sec);

    /**
     * @brief Получить шаг таймера.
     */
    double getTimerStep() const;

    /**
     * @brief Получить информцию об OpenGL
     */
    std::string getOpenGLInfo() const;

    /**
     * @brief Получить строку расширений OpenGL как строку.
     */
    std::string getOpenGLExtensions() const;

    /**
     * @brief Получить строку расширений OpenGL как вектор.
     */
    std::vector<std::string> getOpenGLExtensionsAsVec() const;

    /**
     * @brief Инициализация всех систем в соответствии с тем, что мы установили.
     *
     * В случае удачной инициализации появляется окно с заданными настройками.
     * @note Всю информацию об OpenGL можно получить только проинициализировав
     * его!
     *
     * @return true в случае, если возможно запустить главный цикл.
     */
    bool init();

    /**
     * @brief Запустить главный цикл приложения.
     *
     * Перед запуском главного цикла необходимо проинициализировать все необходимые приложению
     * ресурсы, вызвав @a init
     * @n
     * Пример запуска главного приложения:
     * @code
     * using namespace Core;
     * Application *app = Application::getInstance();
     * app->setWindowTitle("Test");
     * app->setFullScreen(false);
     * app->setSize(glm::ivec2(800, 600));
     * app->setColorDepth(ColorDepth::ColorDepth32);
     * if (app->init()) {
     *     std::cout << app->getOpenGLInfo();
     *     std::cout << app->getOpenGLExtensions();
     *     app->exec();
     * }
     * app->clear();
     * @endcode
     * @sa init
     */
    void exec();

    /**
     * @brief Установить обработчика рисования.
     * @param painter обработчик рисования.
     */
    void setScene(core::AbstractScene *scene);

    /**
     * @brief Подготовить приложение для работы.
     *
     * Здесь загружаются необходимые ресурсы (материалы, шейдеры, изоражения и т.д.)
     */
    void prepareGL();

    /**
     * @brief Обновление состояния.
     *
     * Здесь выполняются действия, связанные с обработкой действий. Это может быть:
     * - перерисовка кадра(e == nullptr)
     * - таймер
     * - клавиатура
     * - мышь
     * - тачпад
     *
     * @param e действие
     * @return true - продолжать работу, false - выход из главного цикла программы.
     */
    bool updateGL(ALLEGRO_EVENT *e);

    /**
     * @brief Перерисовать очередной кадр.
     */
    void paintGL();

    /**
     * @brief Очистить за собой память, занятую под нужды allegro.
     *
     * Конечно, это дело клево былло бы засунуть в деструктор,
     * однако при разрушении из деструктора прога падает по сегфолту.
     *
     * @note Не забудьте очистить за собой память!
     */
    void clear();

    /**
     * @brief Получить промежуток времени, потраченный на последний кадр(в секундах).
     */
    float getSecondOfLastFrame() const;

private:
    CApplication();
    ~CApplication();
    CApplication(const CApplication&);
    CApplication &operator=(const CApplication&);

    /**
     * @brief Подготовить дисплей.
     */
    bool prepareDisplay();
    /**
     * @brief Подготовить таймер.
     */
    bool prepareTimer();
    /**
     * @brief Подготовить клавиатуру.
     */
    bool prepareKeyboard();
    /**
     * @brief Подготовить мышь.
     */
    bool prepareMouse();
    /**
     * @brief Подготовить touchscreen.
     */
    bool prepareTouch();
    /**
     * @brief Подготовить очередь событий.
     */
    void prepareEventQueue();

    static CApplication *instance;

    std::string title;          /**< Заголовок окна. */
    bool fullScreen;            /**< Полный ли экран. */
    glm::ivec2 position;        /**< положение верхнего левого угла окна. */
    glm::ivec2 size;            /**< Размеры окна(Высота, ширина). */
    EColorDepth depth;           /**< Глубина цвета. */

    ALLEGRO_DISPLAY *display;   /**< Дисплей. */
    ALLEGRO_EVENT_QUEUE *queue; /**< Очередь событий. */
    ALLEGRO_TIMER *timer;       /**< Таймер. */

    AbstractScene *painter;           /**< Сцена для рисования. */

    bool isTimerInitialized;    /**< Инициализирован ли таймер. */
    bool isKeyboardInitialized; /**< Инициализирована ли клавиатура. */
    bool isMouseInitialized;    /**< Инициализирована ли мышь. */
    bool isTouchInitialized;    /**< Инициализирован ли тачпад. */
    bool isDisplayInitialized;  /**< Инициализирован ли дисплей. */
    bool isInitialized;         /**< Все ли готово к визуализации. */

    float secOfLastFrame;       /**< Время визуализации последнего кадра. */
}; // class Application

} // namespace Core

#endif /*APPLICATION_H*/
