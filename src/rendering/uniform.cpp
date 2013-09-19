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

    Uniform::Uniform(size_t i, UniformType t, glm::vec4 val)
    {
        index = i;
        type = t;
        vec4Val = val;
    }

    Uniform::Uniform(size_t i, UniformType t, GLuint val)
    {
        index = i;
        type = t;
        textureVal = val;
    }
    
    Uniform::Uniform(const Uniform& other)
    {
        index = other.index;
        type = other.type;
        
        switch(type)
        {
            case FLOAT:
                floatVal = other.floatVal;
                break;
            case VEC2:
                vec2Val = other.vec2Val;
                break;
            case VEC3:
                vec3Val = other.vec3Val;
                break;
            case VEC4:
                vec4Val = other.vec4Val;
                break;
            case TEXTURE:
                textureVal = other.textureVal;
                break;
        }
    }
}
