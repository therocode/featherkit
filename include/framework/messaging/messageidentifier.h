#pragma once
#include <stdint.h>

namespace windbreeze
{
    static uint32_t nextMessageId = 0;

    template<class Type>
    struct MessageIdentifier
    {
        static uint32_t id;
    };

    template<class Type>
    uint32_t MessageIdentifier<Type>::id = nextMessageId++;
}
