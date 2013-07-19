#include <framework/messaging/messageexception.h>

namespace windbreeze
{
    MessageException::MessageException(const std::string& message) : std::runtime_error(message)
    {
    }
}
