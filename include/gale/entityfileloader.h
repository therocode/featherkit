#include <map>
#include <string>

namespace windgale
{
    class EntityFileLoader
    {
        public:
            std::map<std::string, int> loadAttributesJson(const std::string& path);
            std::map<std::string, std::map<std::string, std::string> > loadEntitiesJson(const std::string& path);
    };
}
