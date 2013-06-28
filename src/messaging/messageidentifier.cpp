#include <framework/messaging/messageidentifier.h>

namespace windbreeze
{
    uint32_t nextMessageId = 0;

    template<class Type>
    uint32_t MessageIdentifier<Type>::id = nextMessageId++;
}
