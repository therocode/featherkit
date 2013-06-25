#include <framework/rendering/text.h>

namespace windbreeze
{
    std::string Text::getText() const
    {
        return text;
    }
    
    glm::vec3 Text::getColour() const
    {
        return colour;
    }
    
    void Text::setText(const std::string& t)
    {
        text = t;
    }
    
    void Text::setColour(const glm::vec3& c)
    {
        colour = c;
    }
    
    float Text::getFontSize() const
    {
        return fontSize;
    }
    
    void Text::setFontSize(float size)
    {
        fontSize = size;
    }
    
    int32_t Text::getFont() const
    {
        return font;
    }

    void Text::setFont(int32_t f)
    {
        font = f;
    }
}
