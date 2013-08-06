#include <featherkit/rendering/text.h>

namespace fea
{
    Text::Text(const std::string& t) : text(t), fontSize(24.0f)
    {
        isText = true;
    }

    Text::Text(const std::string& t, float r, float g, float b) : text(t), fontSize(24.0f)
    {
        isText = true;
        setColour(r, b, g);
    }
    
    Text::Text(const std::string& t, const glm::vec3& col) : text(t), fontSize(24.0f)
    {
        isText = true;
        setColour(col);
    }
    
    std::string Text::getText() const
    {
        return text;
    }

    void Text::setText(const std::string& t)
    {
        text = t;
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
