#include <featherkit/rendering/uniform.hpp>

namespace fea
{
    Uniform::Uniform(const std::string& name, UniformType t, float val)
    {
        mName = name;
        mType = t;
        mFloatVal = val;
    }

    Uniform::Uniform(const std::string& name, UniformType t, glm::vec2 val)
    {
        mName = name;
        mType = t;
        mVec2Val = val;
    }

    Uniform::Uniform(const std::string& name, UniformType t, glm::vec3 val)
    {
        mName = name;
        mType = t;
        mVec3Val = val;
    }

    Uniform::Uniform(const std::string& name, UniformType t, glm::vec4 val)
    {
        mName = name;
        mType = t;
        mVec4Val = val;
    }

    Uniform::Uniform(const std::string& name, UniformType t, glm::mat2x2 val)
    {
        mName = name;
        mType = t;
        mMat2x2Val = val;
    }

    Uniform::Uniform(const std::string& name, UniformType t, glm::mat4x4 val)
    {
        mName = name;
        mType = t;
        mMat4x4Val = val;
    }

    Uniform::Uniform(const std::string& name, UniformType t, GLuint val)
    {
        mName = name;
        mType = t;
        mTextureVal = val;
    }
    
    Uniform::Uniform(const Uniform& other)
    {
        mName = other.mName;
        mType = other.mType;
        
        switch(mType)
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
