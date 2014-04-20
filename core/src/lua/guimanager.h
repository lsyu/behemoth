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

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "abstracteventlistener.h"
#include "basicluamanager.h"

#include "lua/lua.h"

#include <string>
#include <vector>

namespace bhm {

class CBasic2dEntity;

/**
 * @brief Менеджер GUI.
 *
 * Позволяет загружать элементы интерфейса, описанные с помощью Lua. @n
 *
 * Элементы GUI:
 * - glm::vec2 - 2хмерный вектор
 * - glm::vec3 - 3хмерный вектор
 * - ui:rectangle - прямоугольник
 * - ui:border - грани прямоугольника
 * - ui:radius - радиус скруглений углов прямоугольника
 * - ui:text - текст для вывода
 *
 * @todo Пример описания интерфейса
 *
 */
class CGUIManager : public AbstractEventListener, public CBasicLuaManager
{
    friend class CEntity2dFactory;
public:
    static CGUIManager *getInstance();

    // AbstractEventListener interface
public:
    virtual bool onClick(AbstractEntity *entity) override;
    virtual bool onPressed(AbstractEntity *entity) override;
    virtual bool onReleased(AbstractEntity *entity) override;
    virtual bool onUpdate(AbstractEntity *entity) override;
protected:
    virtual bool executeAction(AbstractEntity *entity, const std::string &action) override;

    // CGUIManager interface
protected:
    /**
     * @brief Прочитать файл описания интерфейса с именем @a fileName.
     *
     * После парсинга скрипта луа наши декларативно описанные элементы
     * сохраняются в вектор. @n
     * Для получения корневого элемента используйте CEntity2dFactory::loadGUI
     * @return true если скрипт выполнен, false в противном случае.
     */
    bool readGui(const std::string &fileName);
    /**
     * @brief добавить готовый объект в контейнер на вывод.
     */
    void addObject(CBasic2dEntity *entity);
    /**
     * @brief Регистрация таблицы ui и всех содержащихся в ней элементов.
     */
    void registerUI();
    /**
     * @brief Регистрация glm::vec2
     */
    void registerVec2();
    /**
     * @brief Регистрация glm::vec3
     */
    void registerVec3();
    /**
     * @brief регистрация behemoth::CBorder
     */
    void registerBorder();
    /**
     * @brief регистрация behemoth::CGradient
     */
    void registerGradient();
    /**
     * @brief Регистрация behemoth::RectangleText.
     */
    void registerText();
    /**
     * @brief Регистрация behemoth::Rectangle.
     */
    void registerRectangle();

private:
    CGUIManager();
    virtual ~CGUIManager();
    CGUIManager(const CGUIManager &);
    CGUIManager &operator=(const CGUIManager&);

    static CGUIManager *instance;
    std::vector< bhm::CBasic2dEntity* > m_objects; /**< Элементы GUI */

    friend class __CGUIManagerImplDel;
}; // class CGUIManager

} // namespace behemoth

#endif // GUIMANAGER_H
