#pragma once
#include <fea/config.hpp>
#include <stdexcept>

namespace fea
{
    class FEA_API FileNotFoundException: public std::runtime_error
    {
        public:
            FileNotFoundException();
            FileNotFoundException(const std::string& message);
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class FileNotFoundException
     *@}
     ***
     *  @class FileNotFoundException
     *  @brief Exception used when a file is not found.
     ***
     *  @fn FileNotFoundException::FileNotFoundException()
     *  @brief Construct a FileNotFoundException instance to throw.
     ***
     *  @fn FileNotFoundException::FileNotFoundException(const std::string& message)
     *  @brief Construct a FileNotFoundException instance to throw.
     *  @param msg Message further explaining the error.
     **/
}
