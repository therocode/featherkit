#pragma once
#include <featherkit/fontstash/fontstash.h>
#include <string>
#include <stdexcept>

namespace fea
{
    class InvalidFontException : public std::runtime_error 
    {
        public:
            InvalidFontException(const std::string& message);
    };
    
    class Font
    {
        public:
            void createFromPath(const std::string& path);
            void createFromData(uint8_t* fontData);
            int32_t getId() const;
        private:
            int32_t fontId;
    };
}
