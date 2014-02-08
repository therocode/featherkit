#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <featherkit/rendering/opengl.h>
#include <featherkit/rendering/colour.h>

namespace fea
{
    enum UniformType{FLOAT, VEC2, VEC3, VEC4, MAT2X2, MAT4X4, TEXTURE};

    struct Uniform
    {
        Uniform(size_t i, UniformType t, float val);
        Uniform(size_t i, UniformType t, glm::vec2 val);
        Uniform(size_t i, UniformType t, glm::vec3 val);
        Uniform(size_t i, UniformType t, glm::vec4 val);
        Uniform(size_t i, UniformType t, glm::mat2x2 val);
        Uniform(size_t i, UniformType t, glm::mat4x4 val);
        Uniform(size_t i, UniformType t, GLuint val);
        Uniform(const Uniform& other);
        size_t mIndex;
        UniformType mType;
        union
        {
            float mFloatVal;
            glm::vec2 mVec2Val;
            glm::vec3 mVec3Val;
            glm::vec4 mVec4Val;
            glm::mat2x2 mMat2x2Val;
            glm::mat4x4 mMat4x4Val;
            GLuint mTextureVal;
        };
    };
}
