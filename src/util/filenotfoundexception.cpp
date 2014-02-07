#include <featherkit/util/filenotfoundexception.h>
#include <string>

namespace fea
{
    namespace util
    {
        FileNotFoundException::FileNotFoundException():runtime_error("File not found")
        {
        }

        FileNotFoundException::FileNotFoundException(const std::string& message):runtime_error(message.c_str())
        {
        }
    }
}
