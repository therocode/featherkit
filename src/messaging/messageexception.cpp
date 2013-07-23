#include <featherkit/messaging/messageexception.h>

namespace fea
{
    MessageException::MessageException(const std::string& message) : std::runtime_error(message)
    {
    }
}
