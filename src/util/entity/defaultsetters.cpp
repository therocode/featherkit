#include <featherkit/util/entity/defaultsetters.h>

namespace fea
{
    namespace util
    {
        DefaultSetterException::DefaultSetterException(const std::string& m) : std::runtime_error(m)
        {
        }

        void floatSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
        {
            float val = std::stof(arguments[0]);

            entity.lock()->setAttribute(attribute, val);
        }
        void doubleSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
        {
            double val = std::stod(arguments[0]);

            entity.lock()->setAttribute(attribute, val);
        }
        void int32Setter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
        {
            int32_t val = std::stoi(arguments[0]);

            entity.lock()->setAttribute(attribute, val);
        }
        void uint32Setter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
        {
            uint32_t val = (uint32_t)std::stoul(arguments[0]);

            entity.lock()->setAttribute(attribute, val);
        }
        void boolSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
        {
            bool val = ((arguments[0] != "false") && (arguments[0] != "0"));

            entity.lock()->setAttribute(attribute, val);
        }
        void byteSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
        {
            uint8_t val = (uint8_t)std::stoul(arguments[0]);

            entity.lock()->setAttribute(attribute, val);
        }
        void idSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
        {
            if(arguments[0] == "#ID#")
            {
                entity.lock()->setAttribute(attribute, entity.lock()->getId());
            }
            else
            {
                throw DefaultSetterException("ERROR! id default setter expects #ID# as value!\n");
            }
        }
    }
}
