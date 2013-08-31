#include <featherkit/util/filenotfoundexception.h>
#include <string>

namespace fea
{
    namespace util
    {
        FileNotFoundException::FileNotFoundException():runtime_error("File not found")
        {
        }

        FileNotFoundException::FileNotFoundException(std::string msg):runtime_error(msg.c_str())
        {
        }
    }
}
