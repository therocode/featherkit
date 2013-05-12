#include "../entity/entity.h"
#include <string>
#include <vector>

namespace windgale
{
    class DefaultSetterException : public std::runtime_error 
    {
        public:
            DefaultSetterException(const std::string& m) 
                : std::runtime_error(m) { };
    };

    void floatSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void doubleSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void int32Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void uint32Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void boolSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void byteSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void idSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
}
