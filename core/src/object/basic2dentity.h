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

#include "abstractentity.h"

namespace core {

class CEventMouseClick;

struct Border {
    Border() : width(0), color(0.0f, 0.0f, 0.0f) {}
    Border(const Border &other) : width(other.width), color(other.color) {}

    float width;
    glm::vec3 color;
}; // struct Border

class Basic2dEntity : public AbstractEntity
{
public:
    Basic2dEntity();
    explicit Basic2dEntity(const std::string &id);
    virtual ~Basic2dEntity();

    virtual std::string getId() const override;

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

    std::vector<AbstractEntity *> vChilds;    /**< вектор детей */
    AbstractEntity *parent;                  /**< родитель */
}; // class Basic2dEntity

} // namespace core

#endif // BASIC2DENTITY_H
