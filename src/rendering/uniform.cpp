#include <featherkit/rendering/uniform.h>

namespace fea
{
    Uniform::Uniform(size_t i, UniformType t, float val)
    {
        index = i;
        type = t;
        mFloatVal = val;
    }

    Uniform::Uniform(size_t i, UniformType t, glm::vec2 val)
    {
        index = i;
        type = t;
        mVec2Val = val;
    }

    Uniform::Uniform(size_t i, UniformType t, glm::vec3 val)
    {
        index = i;
        type = t;
        mVec3Val = val;
    }

    Uniform::Uniform(size_t i, UniformType t, glm::vec4 val)
    {
        index = i;
        type = t;
        mVec4Val = val;
    }

    Uniform::Uniform(size_t i, UniformType t, glm::mat2x2 val)
    {
        index = i;
        type = t;
        mMat2x2Val = val;
    }

    Uniform::Uniform(size_t i, UniformType t, glm::mat4x4 val)
    {
        index = i;
        type = t;
        mMat4x4Val = val;
    }

    Uniform::Uniform(size_t i, UniformType t, GLuint val)
    {
        index = i;
        type = t;
        mTextureVal = val;
    }
    
    Uniform::Uniform(const Uniform& other)
    {
        index = other.index;
        type = other.type;
        
        switch(type)
        {
            case FLOAT:
                mFloatVal = other.mFloatVal;
                break;
            case VEC2:
                mVec2Val = other.mVec2Val;
                break;
            case VEC3:
                mVec3Val = other.mVec3Val;
                break;
            case VEC4:
                mVec4Val = other.mVec4Val;
                break;
            case MAT2X2:
                mMat2x2Val = other.mMat2x2Val;
                break;
            case MAT4X4:
                mMat4x4Val = other.mMat4x4Val;
                break;
            case TEXTURE:
                mTextureVal = other.mTextureVal;
                break;
        }
    }
}
