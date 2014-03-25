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

#ifndef RECTANGLEDECORATION_H
#define RECTANGLEDECORATION_H

namespace behemoth {

/**
 * @brief Грани области.
 */
struct CBorder {
    CBorder() : color(0.0f, 0.0f, 0.0f), width(0) {}

    glm::vec4 toVec4() const {
        return glm::vec4(color, width);
    }

    glm::vec3 color;        /**< цвет */
    float width;            /**< размер */
}; // struct Border

/**
 * @brief Радиус скруглений углов
 * @note Длина радиуса - отношение к половине меньшей стороны прямоугольника.
 * @note Для радиуса верно: 0.0f=0%, 1.0f=100% от половины меньшей стороны прямоугольника.
 */
struct CBorderRadius {
    CBorderRadius() : m_r(0), m_bottomLeft(0), m_topLeft(0), m_topRight(0),m_bottomRight(0) {}
    CBorderRadius(const CBorderRadius &other) : m_r(other.m_r), m_bottomLeft(other.m_bottomLeft),
        m_topLeft(other.m_topLeft), m_topRight(other.m_topRight),m_bottomRight(other.m_bottomRight) {}

    void setRadius(float r) { this->m_r = validateValue(r); }
    float getRadius() const { return m_r; }

    void setBottomLeft(float bottomLeft) { this->m_bottomLeft = validateValue(bottomLeft); }
    float getBottomLeft() const { return m_bottomLeft == 0 ? m_r : m_bottomLeft; }

    void setTopLeft(float topLeft) { this->m_topLeft = validateValue(topLeft); }
    float getTopLeft() const { return m_topLeft == 0 ? m_r : m_topLeft; }

    void setTopRight(float topRight) { this->m_topRight = validateValue(topRight); }
    float getTopRight() const { return m_topRight == 0 ? m_r : m_topRight; }

    void setBottomRight(float bottomRight) { this->m_bottomRight = validateValue(bottomRight); }
    float getBottomRight() const { return m_bottomRight == 0 ? m_r : m_bottomRight; }

    glm::vec4 toVec4() const {
        return glm::vec4(getBottomLeft(), getTopLeft(), getTopRight(), getBottomRight());
    }

    CBorderRadius &operator*(float value) {
        m_r = validateValue(m_r*value);
        m_bottomLeft = validateValue(m_bottomLeft*value);
        m_topLeft = validateValue(m_topLeft*value);
        m_topRight = validateValue(m_topRight*value);
        m_bottomRight = validateValue(m_bottomRight*value);
        return *this;
    }

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
    float m_r;
    float m_bottomLeft;
    float m_topLeft;
    float m_topRight;
    float m_bottomRight;
}; // struct CBorderRadius

/**
 * @brief Градиент.
 */
struct CGradient{
    CGradient() : m_bottomLeft(), m_topLeft(), m_topRight(), m_bottomRight() {}
    CGradient(const glm::vec3 &bottomLeft, const glm::vec3 &topLeft, const glm::vec3 &topRight, const glm::vec3 &bottomRight)
        :m_bottomLeft(bottomLeft), m_topLeft(topLeft), m_topRight(topRight), m_bottomRight(bottomRight) {}

    glm::vec3 m_bottomLeft;
    glm::vec3 m_topLeft;
    glm::vec3 m_topRight;
    glm::vec3 m_bottomRight;
}; // struct CGradient

} // namespace behemoth

#endif // RECTANGLEDECORATION_H
