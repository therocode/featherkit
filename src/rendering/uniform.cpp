#include <featherkit/rendering/uniform.h>

namespace fea
{
    Uniform::Uniform(size_t i, UniformType t, float val)
    {
        index = i;
        type = t;
        floatVal = val;
    }

    Uniform::Uniform(size_t i, UniformType t, glm::vec2 val)
    {
        index = i;
        type = t;
        vec2Val = val;
    }

    Uniform::Uniform(size_t i, UniformType t, glm::vec3 val)
    {
        index = i;
        type = t;
        vec3Val = val;
    }
}
