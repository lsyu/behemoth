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

#ifndef BASIC2DENTITY_H
#define BASIC2DENTITY_H

#include "core/objects/abstractentity.h"

namespace core {

class CEventMouseClick;
class CApplication;
class DefaultScene;

/**
 * @brief Грани области.
 */
struct CBorder {
    CBorder() : width(0), color(0.0f, 0.0f, 0.0f) {}
    CBorder(const CBorder &other) : width(other.width), color(other.color) {}

    float width;        /**< размер */
    glm::vec3 color;    /**< цвет */
}; // struct Border

/**
 * @brief Базовая сущность для генерирования и вывода пользовательского интерфейса.
 */
class CBasic2dEntity : public AbstractEntity
{
public:

    friend class CApplication;
    friend class CBasicGUILayer;

    CBasic2dEntity();
    explicit CBasic2dEntity(const std::string &id);
    virtual ~CBasic2dEntity();

    virtual std::string getId() const override;
    void setId(const std::string &id);

    virtual void setParent(AbstractEntity *parent) override;
    virtual AbstractEntity *getParent() const override;
    virtual bool isRoot() const override;

    virtual void addChild(AbstractEntity *child) override;
    virtual AbstractEntity *getChild(const std::string &id) override;
    virtual std::vector<AbstractEntity *> &getChilds() override;

    /**
     * @brief Обработка клика
     */
    virtual void onClicked(const CEventMouseClick &event) = 0;

protected:
    std::string id;                         /**< идентификатор */
    std::vector<glm::vec2> vPos2;           /**< вектор координат */
    std::vector<glm::vec2> vUV;             /**< вектор текстурных координат */
    std::vector<glm::vec3> vColor;          /**< вектор цветов вершин */

    std::vector<AbstractEntity *> vChilds;  /**< вектор детей */
    AbstractEntity *parent;                 /**< родитель */

    static std::vector<CBasic2dEntity*> objects4Event;   /**< Объекты, для которых выполнилось
                                                         * действие.
                                                         */
}; // class Basic2dEntity

} // namespace core

#endif // BASIC2DENTITY_H
