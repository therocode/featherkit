#pragma once
#include <cstdint>

namespace fea
{
    enum UniformType{FLOAT, VEC2, VEC3};

    struct Uniform
    {
        Uniform(size_t i, UniformType t, float val);
        Uniform(size_t i, UniformType t, glm::vec2 val);
        Uniform(size_t i, UniformType t, glm::vec3 val);
        size_t index;
        UniformType type;
        union
        {
            float floatVal;
            glm::vec2 vec2Val;
            glm::vec3 vec3Val;
        };
    };
}
