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
        FEA_ASSERT(size > 0.0f, "Size of fonts must be a non-zero positive integer! " + std::to_string(size
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
