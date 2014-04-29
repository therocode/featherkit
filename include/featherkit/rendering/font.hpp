#pragma once
#include <string>
#include <functional>
#include <stdexcept>
#include <cstdint>

namespace fea
{
    class InvalidFontException : public std::runtime_error 
    {
        public:
            InvalidFontException(const std::string& message);
    };

    class TextSurface;
    
    class Font
    {
        public:
            Font(const std::string& path = "", const float size = 12.0f);
            const std::string& getPath() const;
            float getSize() const;
            bool operator==(const Font& other) const;
        private:
            std::string mFontPath;
            float mFontSize;
    };
    
    /** @addtogroup Render2D
     *@{
     *  @class Font
     *@}
     ***
     *  @class Font
     *  @brief Font object to use with fea::TextSurface
     *
     *  The font object holds font data which is used by the fea::TextSurface class when writing text. Fonts can right now only be loaded from file. The size given to a font object is important since it will determine the resolution and memory foot print of the font. A font with a bigger size will look more smooth, but also take upp more memory and vice versa. 
     ***
     *  @fn Font::Font(const std::string& path = "", const float size = 12.0f)
     *  @brief Construct a font from the given file name and size.
     *
     *  Assert/undefined behavior if the size is zero or less.
     *  @param path Path to file.
     *  @param size Size of the font.
     ***
     *  @fn const std::string& Font::getPath() const
     *  @brief Get the current path in use.
     *  @return The path.
     ***
     *  @fn float Font::getSize() const
     *  @brief Get the current size of the font.
     *  @return The size.
     ***
     *  @fn bool Font::operator==(const Font& other) const
     *  @brief Compare two font instances.
     *  @param other Font to compare with.
     *  @return True if the instances are the same.
     ***/
}

#include <featherkit/rendering/font.inl>
