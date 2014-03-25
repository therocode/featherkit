#include <featherkit/ui/inputfilenotfoundexception.hpp>
#include <string>

namespace fea
{
    InputFileNotFoundException::InputFileNotFoundException():runtime_error("InputFile not found")
    {
    }

    InputFileNotFoundException::InputFileNotFoundException(const std::string& message):runtime_error(message.c_str())
    {
    }
}
