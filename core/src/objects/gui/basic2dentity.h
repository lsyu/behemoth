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

#ifndef BASIC2DENTITY_H
#define BASIC2DENTITY_H

#include "core/objects/abstractentity.h"

namespace behemoth {

class CEventMouseClick;
class CApplication;
class DefaultScene;


/**
 * @brief Радиус скруглений углов
 * @note Длина радиуса - отношение к половине меньшей стороны прямоугольника.
 * @note Для радиуса верно: 0.0f=0%, 1.0f=100% от половины меньшей стороны прямоугольника.
 */
struct CBorderRadius {
    CBorderRadius() : r(0), bottomLeft(0), topLeft(0), topRight(0),bottomRight(0) {}
    CBorderRadius(const CBorderRadius &other) : r(other.r), bottomLeft(other.bottomLeft),
        topLeft(other.topLeft), topRight(other.topRight),bottomRight(other.bottomRight) {}

    void setRadius(float r) { this->r = validateValue(r); }
    float getRadius() const { return r; }

    void setBottomLeft(float bottomLeft) { this->bottomLeft = validateValue(bottomLeft); }
    float getBottomLeft() const { return bottomLeft == 0 ? r : bottomLeft; }

    void setTopLeft(float topLeft) { this->topLeft = validateValue(topLeft); }
    float getTopLeft() const { return topLeft == 0 ? r : topLeft; }

    void setTopRight(float topRight) { this->topRight = validateValue(topRight); }
    float getTopRight() const { return topRight == 0 ? r : topRight; }

    void setBottomRight(float bottomRight) { this->bottomRight = validateValue(bottomRight); }
    float getBottomRight() const { return bottomRight == 0 ? r : bottomRight; }

private:
    // from 0 to 1
    float validateValue(float val)
    {
        if (val < 0.0)
            val *= -1.0f;
        if (val > 1.0f)
            val -= static_cast<float>(static_cast<int>(val));
        return val;
    }
    float r;
    float bottomLeft;
    float topLeft;
    float topRight;
    float bottomRight;
}; // struct CBorderRadius

/**
 * @brief Грани области.
 */
struct CBorder {
    CBorder() : width(0), color(0.0f, 0.0f, 0.0f) {}
    CBorder(const CBorder &other) : width(other.width), color(other.color) {}

    float width;            /**< размер */
    glm::vec3 color;        /**< цвет */
}; // struct Border

/**
 * @brief Градиент.
 */
struct CGradient{
    CGradient() : bottomLeft(), topLeft(), topRight(), bottomRight() {}
    CGradient(const glm::vec3 &bottomLeft, const glm::vec3 &topLeft, const glm::vec3 &topRight, const glm::vec3 &bottomRight)
        :bottomLeft(bottomLeft), topLeft(topLeft), topRight(topRight), bottomRight(bottomRight) {}

    glm::vec3 bottomLeft;
    glm::vec3 topLeft;
    glm::vec3 topRight;
    glm::vec3 bottomRight;
}; // struct CGradient

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
    /**
     * @brief Установить родителя.
     */
    virtual void setParent(CBasic2dEntity *parent);
    /**
     * @brief Получить родителя сущности.
     */
    virtual CBasic2dEntity *getParent() const;
    bool isRoot() const;
    /**
     * @brief getChild Получить ребенка сущности по его имени.
     * @note В случае, если ребенка с именем id не найдено, вернется nullptr.
     */
    virtual CBasic2dEntity *getChild(const std::string &id) final;
    /**
     * @brief getChilds Получить вектор детей сущности.
     */
    virtual std::vector<CBasic2dEntity *> &getChilds() final;

    /**
     * @brief Добавить ребенка сущности.
     */
    virtual void addChild(CBasic2dEntity *child);
    /**
     * @brief Получить минимальную абсциссу ограничивающей поверхности.
     */
    virtual float getXMin() const = 0;
    /**
     * @brief Получить максимальную абсциссу ограничивающей поверхности.
     */
    virtual float getXMax() const = 0;
    /**
     * @brief Получить минимальную оординату ограничивающей поверхности.
     */
    virtual float getYMin() const = 0;
    /**
     * @brief Получить максимальную оординату ограничивающей поверхности.
     */
    virtual float getYMax() const = 0;

    /**
     * @brief Обработка клика
     */
    virtual void onClicked(const CEventMouseClick &event) = 0;

protected:
    std::string id;                         /**< идентификатор */
    std::vector<glm::vec2> vPos2;           /**< вектор координат */
    std::vector<glm::vec2> vUV;             /**< вектор текстурных координат */
    std::vector<glm::vec3> vColor;          /**< вектор цветов вершин */

    std::vector<CBasic2dEntity *> vChilds;  /**< вектор детей */
    CBasic2dEntity *parent;                 /**< родитель */

    static std::vector<CBasic2dEntity*> objects4Event;   /**< Объекты, для которых выполнилось
                                                         * действие.
                                                         */
}; // class Basic2dEntity

} // namespace behemoth

#endif // BASIC2DENTITY_H
