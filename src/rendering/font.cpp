#include <featherkit/rendering/font.h>
#include <featherkit/rendering/textsurface.h>
#include <sstream>
#include <sys/stat.h>

namespace fea
{
    InvalidFontException::InvalidFontException(const std::string& message) : std::runtime_error(message)
    {
    }
    
    Font::Font(const std::string& path, const float size) : fontPath(path), fontSize(size)
    {
    }
    
    void Font::setPath(const std::string& path)
    {
        fontPath = path;
    }
    
    void Font::setSize(const float size)
    {
        fontSize = size;
    }

    const std::string& Font::getPath() const
    {
        return fontPath;
    }
    
    float Font::getSize() const
    {
        return fontSize;
    }
            
    bool Font::operator==(const Font& other) const
    {
        return fontPath == other.fontPath && (uint32_t)(fontSize * 100.0f) == (uint32_t)(other.fontSize * 100.0f);
    }
}
