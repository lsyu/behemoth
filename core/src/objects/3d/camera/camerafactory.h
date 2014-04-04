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

#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include "abstractcamera.h"
#include <map>
#include <string>

namespace behemoth {

/**
 * @brief Фабрика загрузки камер.
 */
class CCameraFactory
{
public:
    /**
     * @brief Получить экземпляр фабрики камер.
     * @return экземпляр фабрики камер.
     */
    static CCameraFactory* getInstance();

    /**
     * @brief Получить камеру по имени.
     * @param name имя камеры.
     * @return камера с заданным именем.
     * @note в случае невозможности создать камеру с заданными параметрами возвращает nullptr.
     */
    AbstractCamera *getCamera(const std::string &name) const;

    /**
     * @brief Получить активную камеру.
     * @note В случае, если камера не установлена, вернется nullptr.
     */
    AbstractCamera *getActiveCamera() const;
    /**
     * @brief Установить активную камеру.
     */
    void setActiveCamera(AbstractCamera *activeCamera);

    /**
     * @brief Получить камеру с перспективной проекцией.
     * @param name имя камеры.
     * @param widthOfVieport ширина зоны просмотра (viewport).
     * @param heightOfVieport высота зоны просмотра (viewport).
     * @param nearPlane ближняя плоскость отсечения.
     * @param farPlane дальняя плоскость отсечения.
     */
    void makePerspectiveCamera(const std::string &name, float widthOfVieport,
                                         float heightOfVieportf, float fov = 45.0f,
                                         float nearPlane = 1.0f, float farPlane = 100.0f);

    /**
     * @brief Получить камеру с ортогональной проекцией.
     * @param name имя камеры.
     * @param left левая граница отсечения.
     * @param right правая граница отсечения.
     * @param bottom нижняя граница отсечения.
     * @param top верхняя граница отсечения.
     * @param near ближняя граница отсечения.
     * @param far дальняя граница отсечения.
     */
    void makeOrthoCamera(const std::string &name, float left, float right, float bottom,
                                   float top, float near, float far);

private:
    CCameraFactory();
    ~CCameraFactory();
    CCameraFactory(const CCameraFactory &);
    CCameraFactory &operator=(const CCameraFactory &);

    static CCameraFactory *instance;
    std::map<std::string, AbstractCamera*> m_cameras;   /**< Контейнер камер. */
    AbstractCamera *m_activeCamera;                     /**< Активная камера. */

    friend class __CCameraFactoryImplDel;
}; // class CCameraFactory

} // namespace behemoth

#endif // CAMERAFACTORY_H
