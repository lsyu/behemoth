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

#ifndef CSCENE3DMANAGER_H
#define CSCENE3DMANAGER_H

#include "abstracteventlistener.h"
#include "basicluamanager.h"

#include "lua/lua.h"

#include <string>
#include <vector>

namespace behemoth {

class CObject3d;

/**
 * @brief Менеджер 3D-сцены.
 *
 * Позволяет загружать трехмерную сцену, описанную с помощью Lua.
 */
class CScene3dManager : public AbstractEventListener, public CBasicLuaManager
{
    friend class CObjectFactory;
    friend class CCameraFactory;
    friend class CLightFactory;
public:
    static CScene3dManager *getInstance();

    // AbstractEventListener interface
public:
    virtual bool onClick(AbstractEntity *entity);
    virtual bool onPressed(AbstractEntity *entity);
    virtual bool onReleased(AbstractEntity *entity);
protected:
    virtual bool executeAction(AbstractEntity *entity, const std::string &action);

    // CScene3dManager interface
protected:
    /**
     * @brief Прочитать файл описания сцены с именем @a fileName.
     *
     * После парсинга скрипта луа наши декларативно описанные элементы
     * сохраняются в вектор. @n
     * Для получения корневого элемента используйте CEntityFactory::loadGUI
     * @return true если скрипт выполнен, false в противном случае.
     */
    bool readScene3d(const std::string &fileName);
    /**
     * @brief добавить готовый объект в контейнер на вывод.
     */
    void addObject(CObject3d *object);
    /**
     * @brief Регистрация таблицы s3d (scene3d) и всех содержащихся в ней элементов.
     */
    void registerScene3d();
    /**
     * @brief регистрация объектов
     */
    void registerObject();
    /**
     * @brief регистрация источников света.
     */
    void registerLight();
    /**
     * @brief регистрация камер.
     */
    void registerCamera();

private:
    CScene3dManager();
    virtual ~CScene3dManager();
    CScene3dManager(const CScene3dManager &);
    CScene3dManager &operator =(const CScene3dManager &);

    static CScene3dManager *instance;
    std::vector<CObject3d*> m_objects;/**< Элементы сцены. */

    friend class __CScene3dManagerImplDel;
}; // class CScene3dManager

} // namespace behemoth

#endif // CSCENE3DMANAGER_H
