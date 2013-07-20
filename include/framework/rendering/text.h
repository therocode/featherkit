#pragma once
#include <framework/rendering/drawable2d.h>

namespace fk
{
    class Text : public Drawable2D
    {
        public:
            Text(const std::string& t);
            Text(const std::string& t, const glm::vec3& col);
            std::string getText() const;
            void setText(const std::string& t);
            glm::vec3 getColour() const;
            void setColour(const glm::vec3& col);
            float getTextSize() const;
            void setTextSize(float size);
            int32_t getFont() const;
            void setFont(int32_t f);
        private:
            std::string text;
            glm::vec3 colour;
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
     *  @fn glm::vec3 Text::getColour() const
     *  @brief Get the colour.
     *  @return Vector containing the colour.
     ***
     *  @fn void Text::setColour(const glm::vec3& col)
     *  @brief Set the colour.
     *  @param col Vector containing the colour.
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
