#include <fea/audio/audiofilenotfoundexception.hpp>
#include <string>

namespace fea
{
    AudioFileNotFoundException::AudioFileNotFoundException():runtime_error("AudioFile not found")
    {
    }

    AudioFileNotFoundException::AudioFileNotFoundException(const std::string& message):runtime_error(message.c_str())
    {
    }
}
