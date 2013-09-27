#include <featherkit/rendering/font.h>
#include <featherkit/rendering/textsurface.h>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

namespace fea
{
    InvalidFontException::InvalidFontException(const std::string& message) : std::runtime_error(message)
    {
    }

    Font::Font(TextSurface& surface) : textureFont(nullptr), owner(&surface)
    {
    }
    
    Font::Font(TextSurface& surface, const std::string& path, const float fontSize) : owner(&surface)
    {
        fontPath = path;
        textureFont = texture_font_new(owner->atlas, path.c_str(), fontSize);
    }

    Font::~Font()
    {
        if(textureFont)
            texture_font_delete(textureFont);
    }

    void Font::createFont(const std::string& path, const float fontSize)
    {
        fontPath = path;
        if(textureFont)
            texture_font_delete(textureFont);

        textureFont = texture_font_new(owner->atlas, path.c_str(), fontSize);
    }
            
    void Font::resize(const float fontSize)
    {
        if(textureFont)
        {
            texture_font_delete(textureFont);
            textureFont = texture_font_new(owner->atlas, fontPath.c_str(), fontSize);
        }
    }
}
