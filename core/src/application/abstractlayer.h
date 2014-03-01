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

#ifndef ABSTRACTLAYER_H
#define ABSTRACTLAYER_H

namespace core {

class CEventMouseClick;

/**
 * @brief Интерфейс слоя.
 * Это может быть слой 3D сцены, слой GUI
 */
class AbstractLayer
{
public:
    AbstractLayer();
    virtual ~AbstractLayer();

    /**
     * @brief Подготовить обработчик рисования для работы.
     */
    virtual void prepareGL() = 0;

    /**
     * @brief Обновление состояния в связи с перерисовкой кадра(Не произошло никаких событий)
     * @return true - продолжать работу, false - выход из главного цикла программы.s
     */
    virtual bool updateGL();
    /**
     * @brief Обновление состояния в связи с кликом мыши.
     * @return true - продолжать работу, false - выход из главного цикла программы.
     */
    virtual bool updateGL(CEventMouseClick *e);

    /**
     * @brief Перерисовать очередной кадр.
     */
    virtual void paintGL() = 0;
}; // class AbstractLayer

} // namespace Core

#endif // ABSTRACTLayer_H
