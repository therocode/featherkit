#pragma once
#include <stdexcept>

namespace fku
{
    class FileNotFoundException: public std::runtime_error
    {
        public:
            FileNotFoundException();
            FileNotFoundException(std::string msg);
    };
}
