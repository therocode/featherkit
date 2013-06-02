#pragma once
#include <stdexcept>

namespace windgale
{
    class FileNotFoundException: public std::runtime_error
    {
        public:
            FileNotFoundException():runtime_error("File not found"){}
            FileNotFoundException(std::string msg):runtime_error(msg.c_str()){}
    };
}
