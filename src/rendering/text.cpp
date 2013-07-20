#include <framework/rendering/text.h>

namespace fk
{
    Text::Text(const std::string& t) : text(t), colour(1.0f, 1.0f, 1.0f), fontSize(24.0f)
    {
        isText = true;
    }

    Text::Text(const std::string& t, const glm::vec3& col) : text(t), colour(col), fontSize(24.0f)
    {
        isText = true;
    }
    
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
    
    float Text::getTextSize() const
    {
        return fontSize;
    }
    
    void Text::setTextSize(float size)
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
