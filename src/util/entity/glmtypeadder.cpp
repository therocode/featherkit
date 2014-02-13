#include <featherkit/util/entity/glmtypeadder.h>
#include <featherkit/entity/entityfactory.h>
#include <glm/glm.hpp>

namespace fea
{
    namespace util
    {
        void addGlmDataTypes(EntityFactory& factory)
        {
            factory.addDataType("vec2", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 2, "Wrong amount of parameters! Expected 2, got " + std::to_string(params.size()) + "!");

                return glm::vec2(stof(params[0]), stof(params[1]));
            });

            factory.addDataType("uvec2", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 2, "Wrong amount of parameters! Expected 2, got " + std::to_string(params.size()) + "!");

                FEA_ASSERT(params[0].find('-') == std::string::npos && params[1].find('-') == std::string::npos, "Default value for type uvec2 is not allowed to have negative numbers! Given '" + params[0] + "," + params[1] + "'.");
                FEA_ASSERT(static_cast<unsigned long>(static_cast<uint32_t>(std::stoul(params[0]))) == std::stoul(params[0]) && static_cast<unsigned long>(static_cast<uint32_t>(std::stoul(params[1]))) == std::stoul(params[1]), "Default value '" + params[0] + "," + params[1] + "' given to attribute of uvec2 is too large!");

                return glm::uvec2(static_cast<uint32_t>(std::stoul(params[0])), static_cast<uint32_t>(std::stoul(params[1])));
            });

            factory.addDataType("ivec2", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 2, "Wrong amount of parameters! Expected 2, got " + std::to_string(params.size()) + "!");

                return glm::ivec2(static_cast<int32_t>(std::stoi(params[0])), static_cast<int32_t>(std::stoi(params[1])));
            });

            factory.addDataType("vec3", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 3, "Wrong amount of parameters! Expected 3, got " + std::to_string(params.size()) + "!");

                return glm::vec3(stof(params[0]), stof(params[1]), stof(params[2]));
            });

            factory.addDataType("uvec3", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 3, "Wrong amount of parameters! Expected 3, got " + std::to_string(params.size()) + "!");

                FEA_ASSERT(params[0].find('-') == std::string::npos && params[1].find('-') == std::string::npos && params[2].find('-') == std::string::npos, "Default value for type uvec3 is not allowed to have negative numbers! Given '" + params[0] + "," + params[1] + "," + params[2] + "'.");
                FEA_ASSERT(static_cast<unsigned long>(static_cast<uint32_t>(std::stoul(params[0]))) == std::stoul(params[0]) && static_cast<unsigned long>(static_cast<uint32_t>(std::stoul(params[1]))) == std::stoul(params[1]) && static_cast<unsigned long>(static_cast<uint32_t>(std::stoul(params[2]))) == std::stoul(params[2]), "Default value '" + params[0] + "," + params[1] + "," + params[2] + "' given to attribute of uvec3 is too large!");

                return glm::uvec3(static_cast<uint32_t>(std::stoul(params[0])), static_cast<uint32_t>(std::stoul(params[1])), static_cast<uint32_t>(std::stoul(params[2])));
            });

            factory.addDataType("ivec3", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 3, "Wrong amount of parameters! Expected 3, got " + std::to_string(params.size()) + "!");

                return glm::ivec3(static_cast<int32_t>(std::stoi(params[0])), static_cast<int32_t>(std::stoi(params[1])), static_cast<int32_t>(std::stoi(params[2])));
            });

            factory.addDataType("mat2x2", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 4 || params.size() == 1, "Wrong amount of parameters! Expected 1 or 4, got " + std::to_string(params.size()) + "!");
                if(params.size() == 1)
                    FEA_ASSERT(params[0] == "I", "Only one argument given. Expected 'I' but got '" + params[0] + "'!");
                
                if(params[0] == "I")
                    return glm::mat2x2();
                else
                    return glm::mat2x2(std::stof(params[0]), std::stof(params[1]), std::stof(params[2]), std::stof(params[3]));
            });

            factory.addDataType("mat3x3", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 9 || params.size() == 1, "Wrong amount of parameters! Expected 1 or 9, got " + std::to_string(params.size()) + "!");
                if(params.size() == 1)
                    FEA_ASSERT(params[0] == "I", "Only one argument given. Expected 'I' but got '" + params[0] + "'!");
                
                if(params[0] == "I")
                    return glm::mat3x3();
                else
                    return glm::mat3x3(std::stof(params[0]), std::stof(params[1]), std::stof(params[2]), std::stof(params[3]), std::stof(params[4]), std::stof(params[5]), std::stof(params[6]), std::stof(params[7]), std::stof(params[8]));
            });

            factory.addDataType("mat4x4", [] (const Parameters& params)
            {
                FEA_ASSERT(params.size() == 16 || params.size() == 1, "Wrong amount of parameters! Expected 1 or 16, got " + std::to_string(params.size()) + "!");
                if(params.size() == 1)
                    FEA_ASSERT(params[0] == "I", "Only one argument given. Expected 'I' but got '" + params[0] + "'!");
                
                if(params[0] == "I")
                    return glm::mat4x4();
                else
                    return glm::mat4x4(std::stof(params[0]), std::stof(params[1]), std::stof(params[2]), std::stof(params[3]), std::stof(params[4]), std::stof(params[5]), std::stof(params[6]), std::stof(params[7]), std::stof(params[8]), std::stof(params[9]), std::stof(params[10]), std::stof(params[11]), std::stof(params[12]), std::stof(params[13]), std::stof(params[14]), std::stof(params[15]));
            });
        }
    }
}
