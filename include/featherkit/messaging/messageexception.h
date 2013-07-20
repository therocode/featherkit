#pragma once
#include <stdexcept>

namespace fk
{
    class MessageException : public std::runtime_error 
    {
        public:
            MessageException(const std::string& message);
    };

    /** @addtogroup Messaging
     *@{
     *  @class MessageException
     *@}
     ***
     *  @class MessageException
     *  @brief Exception used by the Messaging when something related to message handling goes wrong.
     ***
     *  @fn MessageException::MessageException(const std::string& message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
     ***/
}
