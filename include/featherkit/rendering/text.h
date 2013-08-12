#pragma once
#include <featherkit/rendering/drawable2d.h>

namespace fea
{
    class Text : public Drawable2D
    {
        public:
            Text(const std::string& t);
            Text(const std::string& t, float r, float g, float b);
            Text(const std::string& t, const glm::vec3& col);
            std::string getText() const;
            void setText(const std::string& t);
            float getTextSize() const;
            void setTextSize(float size);
            int32_t getFont() const;
            void setFont(int32_t f);
        private:
            std::string text;
            float fontSize;
            int font;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Text
     *@}
     ***
     *  @class Text
     *  @brief Drawable2D representing a text string.
     *  
     *  Texts have a font associated with them which must be added to the Renderer2D before any text of that font is rendered.
     *
     *  Texts can be scaled and positioned, but not rotated.
     ***
     *  @fn Text::Text(const std::string& t)
     *  @brief Construct a Text drawable with the given string.
     *  @param t Text string.
     ***
     *  @fn Text::Text(const std::string& t, float r, float g, float b)
     *  @brief Construct a Text drawable with the given string and colour.
     *  @param t Text string.
     *  @param r Amount of red.
     *  @param g Amount of green.
     *  @param b Amount of blue.
     ***
     *  @fn Text::Text(const std::string& t, const glm::vec3& col)
     *  @brief Construct a Text drawable with the given string and colour.
     *  @param t Text string.
     *  @param col Colour.
     ***
     *  @fn std::string Text::getText() const
     *  @brief Get the text.
     *  @return The text.
     ***
     *  @fn void Text::setText(const std::string& t)
     *  @brief Set the text.
     *  @param t Text to set.
     ***
     *  @fn float Text::getTextSize() const
     *  @brief Get the size of the characters in the text.
     *  @return Text size.
     ***
     *  @fn void Text::setTextSize(float size)
     *  @brief Set the size of the characters in the text.
     ***
     *  @fn int32_t Text::getFont() const
     *  @brief Get the font of the text.
     *  @return Numerical ID representing the font.
     ***
     *  @fn void Text::setFont(int32_t f)
     *  @brief Set the font of the text.
     *  @param f Numerical ID representing the font.
     ***/
}
