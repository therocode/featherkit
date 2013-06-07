#pragma once
#include <stdexcept>

class MessageException : public std::runtime_error 
{
    public:
        MessageException(const std::string& message) 
            : std::runtime_error(message) { };
};
