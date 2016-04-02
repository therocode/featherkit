#include <fea/rendering/uniform.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace fea
{
    Uniform::Uniform()
    {
        mType = NO_TYPE;
    }

    Uniform::Uniform(UniformType t, const float val)
    {
        mType = t;
        mFloatVal = val;
    }

    Uniform::Uniform(UniformType t, const int32_t val)
    {
        mType = t;
        mIntVal = val;
    }

    Uniform::Uniform(UniformType t, const glm::vec2& val)
    {
        mType = t;
        mVec2Val[0] = val[0];
        mVec2Val[1] = val[1];
    }

    Uniform::Uniform(UniformType t, const glm::vec3& val)
    {
        mType = t;
        mVec3Val[0] = val[0];
        mVec3Val[1] = val[1];
        mVec3Val[2] = val[2];
    }

    Uniform::Uniform(UniformType t, const glm::vec4& val)
    {
        mType = t;
        mVec4Val[0] = val[0];
        mVec4Val[1] = val[1];
        mVec4Val[2] = val[2];
        mVec4Val[3] = val[3];
    }

    Uniform::Uniform(UniformType t, const glm::mat2x2& val)
    {
        mType = t;
        const float* mat = glm::value_ptr(val);
        mMat2x2Val[0] = mat[0];
        mMat2x2Val[1] = mat[1];
        mMat2x2Val[2] = mat[2];
        mMat2x2Val[3] = mat[3];
    }

    Uniform::Uniform(UniformType t, const glm::mat4x4& val)
    {
        mType = t;
        const float* mat = glm::value_ptr(val);
        mMat4x4Val[0] = mat[0];
        mMat4x4Val[1] = mat[1];
        mMat4x4Val[2] = mat[2];
        mMat4x4Val[3] = mat[3];
        mMat4x4Val[4] = mat[4];
        mMat4x4Val[5] = mat[5];
        mMat4x4Val[6] = mat[6];
        mMat4x4Val[7] = mat[7];
        mMat4x4Val[8] = mat[8];
        mMat4x4Val[9] = mat[9];
        mMat4x4Val[10] = mat[10];
        mMat4x4Val[11] = mat[11];
        mMat4x4Val[12] = mat[12];
        mMat4x4Val[13] = mat[13];
        mMat4x4Val[14] = mat[14];
        mMat4x4Val[15] = mat[15];
    }

    Uniform::Uniform(UniformType t, const GLuint val)
    {
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
            case INT:
                mIntVal = other.mIntVal;
                break;
            case VEC2:
                std::copy(other.mVec2Val, other.mVec2Val + 2, mVec2Val);
                break;
            case VEC3:
                std::copy(other.mVec3Val, other.mVec3Val + 3, mVec3Val);
                break;
            case VEC4:
                std::copy(other.mVec4Val, other.mVec4Val + 4, mVec4Val);
                break;
            case MAT2X2:
                std::copy(other.mMat2x2Val, other.mMat2x2Val + 4, mMat2x2Val);
                break;
            case MAT4X4:
                std::copy(other.mMat4x4Val, other.mMat4x4Val + 16, mMat4x4Val);
                break;
            case TEXTURE:
                mTextureVal = other.mTextureVal;
                break;
            case NO_TYPE:
                break;
        }
    }

    bool Uniform::operator==(const Uniform& other) const
    {
        if(!(mType == other.mType && mName == other.mName))
            return false;
        else
        {
            std::equal(mMat4x4Val, mMat4x4Val + 16, other.mMat4x4Val) && mName == other.mName;

            switch(mType)
            {
                case FLOAT:
                    return mFloatVal == other.mFloatVal;
                case INT:
                    return mIntVal == other.mIntVal;
                case VEC2:
                    return std::equal(other.mVec2Val, other.mVec2Val + 2, mVec2Val);
                case VEC3:
                    return std::equal(other.mVec3Val, other.mVec3Val + 3, mVec3Val);
                case VEC4:
                    return std::equal(other.mVec4Val, other.mVec4Val + 4, mVec4Val);
                case MAT2X2:
                    return std::equal(other.mMat2x2Val, other.mMat2x2Val + 4, mMat2x2Val);
                case MAT4X4:
                    return std::equal(other.mMat4x4Val, other.mMat4x4Val + 16, mMat4x4Val);
                case TEXTURE:
                    return mTextureVal == other.mTextureVal;
                case NO_TYPE:
                    return true;
            }
        }
    }
}
