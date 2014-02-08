#include <featherkit/rendering/font.h>
#include <featherkit/rendering/textsurface.h>
#include <sstream>
#include <sys/stat.h>

namespace fea
{
    InvalidFontException::InvalidFontException(const std::string& message) : std::runtime_error(message)
    {
    }
    
    Font::Font(const std::string& path, const float size) : mFontPath(path), mFontSize(size)
    {
    }
    
    void Font::setPath(const std::string& path)
    {
        mFontPath = path;
    }
    
    void Font::setSize(const float size)
    {
        mFontSize = size;
    }

    const std::string& Font::getPath() const
    {
        return mFontPath;
    }
    
    float Font::getSize() const
    {
        return mFontSize;
    }
            
    bool Font::operator==(const Font& other) const
    {
        return mFontPath == other.mFontPath && (uint32_t)(mFontSize * 100.0f) == (uint32_t)(other.mFontSize * 100.0f);
    }
}
