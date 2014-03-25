#pragma once
#include <stdexcept>

namespace fea
{
    class InputFileNotFoundException: public std::runtime_error
    {
        public:
            InputFileNotFoundException();
            InputFileNotFoundException(const std::string& message);
    };
    /** @addtogroup Input
     *@{
     *  @class InputFileNotFoundException
     *@}
     ***
     *  @class InputFileNotFoundException
     *  @brief Exception used when a file is not found.
     ***
     *  @fn InputFileNotFoundException::InputFileNotFoundException()
     *  @brief Construct a InputFileNotFoundException instance to throw.
     ***
     *  @fn InputFileNotFoundException::InputFileNotFoundException(const std::string& message)
     *  @brief Construct a InputFileNotFoundException instance to throw.
     *  @param msg Message further explaining the error.
     **/
}
