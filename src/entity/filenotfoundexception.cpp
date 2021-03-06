#include <fea/entity/filenotfoundexception.hpp>
#include <string>

namespace fea
{
    FileNotFoundException::FileNotFoundException():runtime_error("File not found")
    {
    }

    FileNotFoundException::FileNotFoundException(const std::string& message):runtime_error(message.c_str())
    {
    }
}
