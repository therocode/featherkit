#pragma once
#include <string>
#include <stdexcept>

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
            void setPath(const std::string& path);
            void setSize(const float size);
            const std::string& getPath() const;
            float getSize() const;
            bool operator==(const Font& other) const;
        private:
            std::string fontPath;
            float fontSize;
    };
}

namespace std
{
    template<>
    struct std::hash<fea::Font>
    {
        public:
            std::size_t operator()(fea::Font const& font) const 
            {
                std::size_t h1 = std::hash<std::string>()(font.getPath());
                std::size_t h2 = std::hash<uint32_t>()((uint32_t)(font.getSize() * 100.0f));
                return h1 ^ (h2 << 1);
            }
    };
}
