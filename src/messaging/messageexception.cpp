#include <featherkit/messaging/messageexception.h>

namespace fk
{
    MessageException::MessageException(const std::string& message) : std::runtime_error(message)
    {
    }
}
