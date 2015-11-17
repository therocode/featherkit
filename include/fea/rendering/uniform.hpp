#pragma once
#include <fea/config.hpp>
#include <cstdint>
#include <string>
#include <glm/glm.hpp>
#include <fea/rendering/opengl.hpp>

namespace fea
{
    enum UniformType{NO_TYPE, FLOAT, VEC2, VEC3, VEC4, MAT2X2, MAT4X4, TEXTURE};

    struct FEA_API Uniform
    {
        Uniform();
        Uniform(const std::string& name, UniformType t, const float val);
        Uniform(const std::string& name, UniformType t, const glm::vec2& val);
        Uniform(const std::string& name, UniformType t, const glm::vec3& val);
        Uniform(const std::string& name, UniformType t, const glm::vec4& val);
        Uniform(const std::string& name, UniformType t, const glm::mat2x2& val);
        Uniform(const std::string& name, UniformType t, const glm::mat4x4& val);
        Uniform(const std::string& name, UniformType t, const GLuint val);
        Uniform(const Uniform& other);

        std::string mName;
        UniformType mType;

        bool operator==(const Uniform& other) const;

        union
        {
            float mFloatVal;           ///<Hold a float value
            float mVec2Val[2];        ///<Hold a vec2 value
            float mVec3Val[3];        ///<Hold a vec3 value
            float mVec4Val[4];        ///<Hold a vec4 value
            float mMat2x2Val[4];    ///<Hold a mat2x2 value
            float mMat4x4Val[16];    ///<Hold a mat4x4 value
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
     *  @fn Uniform::Uniform()
     *  @brief Construct a null uniform.
     ***
     *  @fn Uniform::Uniform(const std::string& name, UniformType t, float val)
     *  @brief Construct a float uniform.
     *  @param name Name.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const std::string& name, UniformType t, glm::vec2 val)
     *  @brief Construct a vec2 uniform.
     *  @param name Name.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const std::string& name, UniformType t, glm::vec3 val)
     *  @brief Construct a vec3 uniform.
     *  @param name Name.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const std::string& name, UniformType t, glm::vec4 val)
     *  @brief Construct a vec4 uniform.
     *  @param name Name.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const std::string& name, UniformType t, glm::mat2x2 val)
     *  @brief Construct a mat2x2 uniform.
     *  @param name Name.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const std::string& name, UniformType t, glm::mat4x4 val)
     *  @brief Construct a mat4x4 uniform.
     *  @param name Name.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const std::string& name, UniformType t, GLuint val)
     *  @brief Construct a texture uniform.
     *  @param name Name.
     *  @param t Type.
     *  @param val Value.
     ***
     *  @fn Uniform::Uniform(const Uniform& other)
     *  @brief Construct a uniform from another uniform.
     *  @param other Uniform to copy.
     ***
     *  @var Uniform::mName
     *  @brief name of the uniform.
     ***
     *  @var Uniform::mType
     *  @brief Type of the uniform.
     ***/
}
