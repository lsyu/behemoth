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

#ifndef RECTANGLETEXT_H
#define RECTANGLETEXT_H

#include "basic2dentity.h"
#include "core/fonts/font.h"
#include <vector>
#include <set>

namespace bhm {

class CRectangleSymbol;

/**
 * @brief Перечисления выравнивания по вертикали
 */
enum class EVerticalAlign : unsigned char {
    top = 0,    /**< По верхнему краю */
    center = 1, /**< По центру */
    bottom = 2  /**< По нижнему краю */
}; // enum EVerticalAlign

/**
 * @brief Перечисления выравнивания по горизонтали
 */
enum class EHorizontalAlign : unsigned char {
    left = 0,   /**< По левому краю */
    center = 1, /**< По центру */
    right = 2   /**< По правому краю */
}; // enum EVerticalAlign

/**
 * @brief Область текста.
 *
 * Текст составляется из объектов CRectangleSymbol.
 */
class CRectangleText : public CBasic2dEntity
{
public:
    friend class CRectangleSymbol;

    CRectangleText();
    virtual ~CRectangleText();

    virtual void paint() const override;
    virtual void onClicked(const CEventMouseClick &event) override;

    virtual void setColor(const glm::vec3 &/*color*/) {}
    virtual float getXMin() const override {return m_x;}
    virtual float getXMax() const override {return m_x+m_width;}
    virtual float getYMin() const override {return m_y;}
    virtual float getYMax() const override {return m_y+m_height;}

    /**
     * @brief Установить цвет шрифта для отображения.
     * @note в соответствии с установленым шрифтом м текстом сгенерируется буферизображения шрифта.
     */
    void setFont(const CFont &font);
    void setFont(const std::string &name);
    std::string getFontName() const;
    void setFont(float height);
    float getFontHeight() const;
//    void setFontQuantity(int quantity);
    void setFontAlign(bhm::EVerticalAlign vAlign);
    EVerticalAlign getVerticalAlign() const;
    void setVerticalAlign(const std::string &vAlign);
    std::string getVericalAlignStr() const;
    void setFontAlign(bhm::EHorizontalAlign hAlign);
    EHorizontalAlign getHorizontalAlign() const;
    void setHorizontalAlign(const std::string &hAlign);
    std::string getHorizontalAlignStr() const;
    /**
     * @brief Установить текст.
     * @note в соответствии с установленым шрифтом м текстом сгенерируется буфер изображения шрифта.
     */
    void setText(const std::string &text);
    std::string getText() const;

protected:
    virtual void configure() override;

private:
    /**
     * @brief Добавить символ.
     */
    void addSymbol(char symbol);

    CFont m_font;                                           /**< Шрифт данного текста. */
    EVerticalAlign m_vAlign;                                /**< Выравнивание по вертикали. */
    EHorizontalAlign m_hAlign;                              /**< Выравнивание по горизонтали. */
    std::vector< std::vector<CRectangleSymbol*> > m_lines;  /**< Сформированные линии текста. */
    std::multiset<CRectangleSymbol*> m_symbols;             /**< Отсортированная последовательность символов. */
    float m_fontHeight;                                     /**< Высота шрифта. */
    std::string m_text;                                     /**< Текст для вывода на экран. */
    float m_x;                                              /**< Абсцисса левого нижнего угла прямоугольника текста. */
    float m_y;                                              /**< Оордината левого нижнего угла прямоугольника текста. */
    float m_width;                                          /**< Длинна выводимого прямоугольника текста. */
    float m_height;                                         /**< Высота выводимого прямоугольника текста. */
}; // class CRectangleFont

} // namespace behemoth

#endif // RECTANGLETEXT_H
