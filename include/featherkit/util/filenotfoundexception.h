#pragma once
#include <stdexcept>

namespace fea
{
    namespace util
    {
        class FileNotFoundException: public std::runtime_error
        {
            public:
                FileNotFoundException();
                FileNotFoundException(const std::string& message);
        };
    }
}
