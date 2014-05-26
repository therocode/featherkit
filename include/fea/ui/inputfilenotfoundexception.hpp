#pragma once
#include <fea/config.hpp>
#include <stdexcept>

namespace fea
{
    class FEA_API InputFileNotFoundException: public std::runtime_error
    {
        public:
            InputFileNotFoundException();
            InputFileNotFoundException(const std::string& message);
    };
    /** @addtogroup UserInterface
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
     *  @param message Message further explaining the error.
     **/
}
