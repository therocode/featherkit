#pragma once
#include <fea/config.hpp>
#include <stdexcept>

namespace fea
{
    class FEA_API AudioFileNotFoundException: public std::runtime_error
    {
        public:
            AudioFileNotFoundException();
            AudioFileNotFoundException(const std::string& message);
    };
    /** @addtogroup Audio
     *@{
     *  @class AudioFileNotFoundException
     *@}
     ***
     *  @class AudioFileNotFoundException
     *  @brief Exception used when a file is not found.
     ***
     *  @fn AudioFileNotFoundException::AudioFileNotFoundException()
     *  @brief Construct a AudioFileNotFoundException instance to throw.
     ***
     *  @fn AudioFileNotFoundException::AudioFileNotFoundException(const std::string& message)
     *  @brief Construct a AudioFileNotFoundException instance to throw.
     *  @param message Message further explaining the error.
     **/
}
