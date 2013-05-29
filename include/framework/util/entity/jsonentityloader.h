#include <map>
#include <string>
#include <stdexcept>

namespace windgale
{
    class FileNotFoundException: public std::runtime_error
    {
        public:
            FileNotFoundException():runtime_error("File not found"){}
            FileNotFoundException(std::string msg):runtime_error(msg.c_str()){}
    };

    class JsonEntityLoader
    {
        public:
            std::map<std::string, int> loadAttributesJson(const std::string& path);
            std::map<std::string, std::map<std::string, std::string> > loadEntitiesJson(const std::string& path);
    };
}
