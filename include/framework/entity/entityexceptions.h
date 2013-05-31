#pragma once
#include <stdexcept>

namespace windgale
{
    using AttributeHash = std::size_t;

    class InvalidIdException : public std::runtime_error 
    {
        public:
            InvalidIdException(const std::string& message) 
                : std::runtime_error(message) { };
    };

    class InvalidAttributeException : public std::runtime_error 
    {
        public:
            InvalidAttributeException(const std::string& m, const AttributeHash h) 
                : std::runtime_error(m), hash(h) { };
            AttributeHash hash;
    };
}
