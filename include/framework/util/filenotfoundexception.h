#pragma once
#include <stdexcept>

namespace fk
{
    class FileNotFoundException: public std::runtime_error
    {
        public:
            FileNotFoundException();
            FileNotFoundException(std::string msg);
    };
}
