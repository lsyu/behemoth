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

#ifndef BASICGUILAYER_H
#define BASICGUILAYER_H

#include "abstractlayer.h"
#include <string>

namespace behemoth {

class CGUIManager;
class CBasic2dEntity;

/**
 * @brief Базовый класс слоя пользовательского интерфейса.
 */
class CBasicGUILayer : public AbstractLayer
{
public:
    explicit CBasicGUILayer(const std::string &fileName);
    virtual ~CBasicGUILayer();

    // AbstractLayer interface
public:
    /**
     * @note Если будешь писать свою реализацию, выполни
     * @code
     * m_root = CEntity2dFactory::getInstance()->loadGUI(fileName);
     * if (m_root)
     *    m_root->configure();
     * @endcode
     */
    virtual void prepareGL() override;
    virtual bool updateGL() override;
    virtual bool updateGL(CEventMouseClick *e) override final;
    /**
     * @note Если будешь писать свою реализацию, выполни что-то похожее на
     * @code
     * glDisable(GL_DEPTH_TEST);
     * glEnable(GL_BLEND);
     * glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     * if (m_root)
     *     m_root->paint();
     * glDisable(GL_BLEND);
     * glEnable(GL_DEPTH_TEST);
     * @endcode
     */
    virtual void paintGL() override;

protected:
    CBasic2dEntity *m_root;     /**< Корневой элемент GUI */

private:
    /**
     * @brief Выполнить действие action
     */
    void executeAction(bool(CGUIManager::*action)(CBasic2dEntity *));

    std::string m_fileName;     /**< Название скрипта описания GUI */
}; // class CBasicGUILayer

} // namespace behemoth

#endif // BASICGUILAYER_H
