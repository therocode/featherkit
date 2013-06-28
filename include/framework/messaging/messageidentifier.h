#pragma once
#include <stdint.h>

namespace windbreeze
{
    template<class Type>
    struct MessageIdentifier
    {
        static uint32_t id;
    };

}
