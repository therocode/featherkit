#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <featherkit/rendering/opengl.hpp>

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
            float mFloatVal;           ///<Hold a float value
            glm::vec2 mVec2Val;        ///<Hold a vec2 value
            glm::vec3 mVec3Val;        ///<Hold a vec3 value
            glm::vec4 mVec4Val;        ///<Hold a vec4 value
            glm::mat2x2 mMat2x2Val;    ///<Hold a mat2x2 value
            glm::mat4x4 mMat4x4Val;    ///<Hold a mat4x4 value
            GLuint mTextureVal;        ///<Hold a texture
        };
    };
    /** @addtogroup Render2D
     *@{
     *  @class Uniform
     *  @enum UniformType
     *@}
     ***
     *  @class Uniform
     *  @brief Defines a uniform variable.
     ***
     *  @enum UniformType
     *  @brief Type of the uniform.
     ***
     *  @fn Uniform::Uniform(size_t i, UniformType t, float val)
     *  @brief Construct a float uniform.
     *  @param i Index.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(size_t i, UniformType t, glm::vec2 val)
     *  @brief Construct a vec2 uniform.
     *  @param i Index.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(size_t i, UniformType t, glm::vec3 val)
     *  @brief Construct a vec3 uniform.
     *  @param i Index.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(size_t i, UniformType t, glm::vec4 val)
     *  @brief Construct a vec4 uniform.
     *  @param i Index.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(size_t i, UniformType t, glm::mat2x2 val)
     *  @brief Construct a mat2x2 uniform.
     *  @param i Index.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(size_t i, UniformType t, glm::mat4x4 val)
     *  @brief Construct a mat4x4 uniform.
     *  @param i Index.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(size_t i, UniformType t, GLuint val)
     *  @brief Construct a texture uniform.
     *  @param i Index.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const Uniform& other)
     *  @brief Construct a uniform from another uniform.
     *  @param other Uniform to copy.
     ***
     *  @var Uniform::mIndex
     *  @brief Index of the uniform.
     ***
     *  @var Uniform::mType
     *  @brief Type of the uniform.
     ***/
}
