#pragma once
#include <stdexcept>

namespace windgale
{
    class FileNotFoundException: public std::runtime_error
    {
        public:
            FileNotFoundException();
            FileNotFoundException(std::string msg);
    };
}
