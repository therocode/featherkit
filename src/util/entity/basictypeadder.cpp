#include <fea/util/entity/basictypeadder.hpp>
#include <fea/entity/entityfactory.hpp>

namespace fea
{
    namespace util
    {
        void addBasicDataTypes(EntityFactory& factory)
        {
            factory.addDataType("bool", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(params[0] == "true" || params[0] == "false", "Bool default arguments must be either 'true' or 'false'! '" + params[0] + "' provided.");

                return params[0] != "false";
            });

            factory.addDataType("float", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");

                return std::stof(params[0]);
            });

            factory.addDataType("double", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");

                return std::stod(params[0]);
            });

            factory.addDataType("uint8", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(params[0].find('-') == std::string::npos, "Default value for type uint8 is not allowed to be negative! Given '" + params[0] + "'.");
                FEA_ASSERT(static_cast<unsigned long>(static_cast<uint8_t>(std::stoul(params[0]))) == std::stoul(params[0]), "Default value '" + params[0] + "' given to attribute of uint8 is too large!");

                return static_cast<uint8_t>(std::stoul(params[0]));
            });

            factory.addDataType("int8", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(static_cast<int>(static_cast<int8_t>(std::stoi(params[0]))) == std::stoi(params[0]), "Default value '" + params[0] + "' given to attribute of int8 is too large/small!");

                return static_cast<int8_t>(std::stoi(params[0]));
            });

            factory.addDataType("uint16", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(params[0].find('-') == std::string::npos, "Default value for type uint16 is not allowed to be negative! Given '" + params[0] + "'.");
                FEA_ASSERT(static_cast<unsigned long>(static_cast<uint16_t>(std::stoul(params[0]))) == std::stoul(params[0]), "Default value '" + params[0] + "' given to attribute of uint16 is too large!");

                return static_cast<uint16_t>(std::stoul(params[0]));
            });

            factory.addDataType("int16", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(static_cast<int>(static_cast<int16_t>(std::stoi(params[0]))) == std::stoi(params[0]), "Default value '" + params[0] + "' given to attribute of int16 is too large/small!");

                return static_cast<int16_t>(std::stoi(params[0]));
            });

            factory.addDataType("uint32", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(params[0].find('-') == std::string::npos, "Default value for type uint32 is not allowed to be negative! Given '" + params[0] + "'.");
                FEA_ASSERT(static_cast<unsigned long>(static_cast<uint32_t>(std::stoul(params[0]))) == std::stoul(params[0]), "Default value '" + params[0] + "' given to attribute of uint32 is too large!");

                return static_cast<uint32_t>(std::stoul(params[0]));
            });

            factory.addDataType("int32", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");

                return static_cast<int32_t>(std::stoi(params[0]));
            });
            
            factory.addDataType("uint64", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(params[0].find('-') == std::string::npos, "Default value for type uint64 is not allowed to be negative! Given '" + params[0] + "'.");

                return static_cast<uint64_t>(std::stoull(params[0]));
            });

            factory.addDataType("int64", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");

                return static_cast<int64_t>(std::stoll(params[0]));
            });
            
            factory.addDataType("string", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                return params[0];
            });

            factory.addDataType("entityptr", [&factory] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 1, "Wrong amount of parameters! Expected 1, got " + std::to_string(params.size()) + "!");
                FEA_ASSERT(factory.hasTemplate(params[0]), "Entity pointer default value must be a valid entity template! '" + params[0] + "' provided.");

                return factory.instantiate(params[0]);
            });
        }
    }
}
