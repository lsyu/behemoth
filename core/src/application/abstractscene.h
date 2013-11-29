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

#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

namespace core {

class CEvent;

/**
 * @brief Интерфейс сцены.
 */
class AbstractScene
{
public:
    AbstractScene();
    virtual ~AbstractScene();

    /**
     * @brief Подготовить обработчик рисования для работы.
     *
     * Здесь загружаются необходимые ресурсы (материалы, шейдеры, изоражения и т.д.)
     */
    virtual void prepareGL() = 0;
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
    virtual bool updateGL(CEvent *e) = 0;

    /**
     * @brief Перерисовать очередной кадр.
     */
    virtual void paintGL() = 0;
}; // class AbstractScene

} // namespace Core

#endif // ABSTRACTSCENE_H
