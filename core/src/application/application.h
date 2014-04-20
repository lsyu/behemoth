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

/**
 * @mainpage Документация проекта behemoth.
 *
 * @section What Содержание
 * - @ref Description
 * - @ref License
 * @n
 * @n
 * @n
 *
 * @section Description Описание
 * behemoth - графический движок с декларативным описанием элементов, основанном на lua,
 * предназначенный для разработки пользовательского интерфейса и трехмерных сцен различной сложности,
 * написанный на C++. @n
 * Использует API OpenGL для рендерига. @n
 * Url проекта: https://github.com/lsyu/behemoth
 *
 * Данный проект базируется на нескольких очень классных проектах:
 * - glm - библиотека линейной алгебры для opengl (http://glm.g-truc.net/0.9.5/index.html)
 * - gli - библиотека работы с изображениями в формате *.dds (http://www.g-truc.net/project-0024.html)
 * - freeglut - открытая альтернатива OpenGL Utility Toolkit (GLUT) (http://freeglut.sourceforge.net/)
 * - freetype - библиотека для растеризации шрифтов и операций над ними (http://www.freetype.org/freetype2/)
 * - lua - втраиваемый интерпритируемый язык программирования (http://www.lua.org/)
 * @n
 * @n
 * @n
 *
 * @section License Лицензия
 * Перевод текста лицензии: @n
 * Это свободная программа: вы можете перераспространять ее и/или изменять
 * ее на условиях Стандартной общественной лицензии GNU в том виде, в каком
 * она была опубликована Фондом свободного программного обеспечения; либо
 * версии 3 лицензии, либо (по вашему выбору) любой более поздней версии.
 *
 * Эта программа распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 *
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.
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

namespace bhm {

class AbstractEvent;
class AbstractLayer;

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
    friend class AbstractLayer;

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
     *     using namespace behemoth;
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
     * @brief Установить слой GUI.
     */
    void setGUILayer(AbstractLayer *guiLayer);

    /**
     * @brief Установить слой 3D сцены.
     */
    void setScene3DLayer(AbstractLayer *scene3D);

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
    /**
     * @brief Получить соотношение сторон.
     */
    float getAspectRatio() const;

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

    std::string m_title;          /**< Заголовок окна. */
    bool m_isFullScreen;          /**< Отображать ли окно в полный экран. */
    glm::ivec2 m_position;        /**< положение верхнего левого угла окна. */
    glm::ivec2 m_size;            /**< Размеры окна(Высота, ширина). */
    glm::ivec2 m_displaySize;     /**< Размеры экрана. */
    EColorDepth m_depth;          /**< Глубина цвета. */
    AbstractLayer *m_guiLayer;    /**< Слой пользовательского интерфейса. */
    AbstractLayer *m_sceneLayer;  /**< Слой трехмерной сцены. */
    int m_windowId;               /**< Идентификатор окна. */
    float m_secOfLastFrame;       /**< Время визуализации последнего кадра. */

    friend class __CApplicationImplDel;
}; // class Application

} // namespace behemoth

#endif /*APPLICATION_H*/
