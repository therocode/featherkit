#include <framework/util/filenotfoundexception.h>

namespace windgale
{
    FileNotFoundException::FileNotFoundException():runtime_error("File not found")
    {
    }

    FileNotFoundException::FileNotFoundException(std::string msg):runtime_error(msg.c_str())
    {
    }
}
