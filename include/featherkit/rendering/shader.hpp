#pragma once
#include <featherkit/rendering/uniform.hpp>
#include <featherkit/rendering/vertexattribute.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>

namespace fea
{
    class GLSLException : public std::runtime_error 
    {
        public:
            GLSLException(const std::string& message);
    };

    class Shader
    {
        public:
            void setSource(const std::string& vertexSource, const std::string& fragmentSource);
            void activate() const;
            void deactivate() const;
            void setUniform(size_t index, UniformType type, const void* value) const;
            void setVertexAttribute(size_t index, const uint32_t floatAmount, const float* data) const;
            void compile();
        private:
            GLuint mProgramId;
            std::unordered_map<size_t, GLint> mUniformLocations;
            std::unordered_map<size_t, GLint> mVertexAttributeLocations;
            std::string mVertexSource;
            std::string mFragmentSource;
            mutable std::vector<GLint> mEnabledVertexAttributes;
    };
    /** @addtogroup Render2D
     *@{
     *  @class GLSLException
     *  @class Shader
     *@}
     ***
     *  @class GLSLException
     *  @brief Exception used when a shader compilation fails.
     ***
     *  @fn GLSLException::GLSLException(const std::string& message)
     *  @brief Construct a GLSLException instance to throw.
     *  @param message Message further explaining the error.
     ***
     *  @class Shader
     *  @brief A representation of a shader which can be used by the renderer2d for rendering.
     ***
     *  @fn void Shader::setSource(const std::string& vertexSource, const std::string& fragmentSource)
     *  @brief Set which GLSL source code the shader should use.
     ***
     *  @fn void Shader::activate() const
     *  @brief Bind the shader for use.
     *
     *  There is no need to call this if the Renderer2D class is used for rendering since it will call it internally.
     ***
     *  @fn void Shader::deactivate() const
     *  @brief Unbind the shader.
     *
     *  There is no need to call this if the Renderer2D class is used for rendering since it will call it internally.
     ***
     *  @fn void Shader::setUniform(size_t index, UniformType type, const void* value) const
     *  @brief Set a uniform variable in the shader.
     *  @param index Index of the uniform to set.
     *  @param type Type of the uniform.
     *  @param value Void pointer to the data.
     ***
     *  @fn void Shader::setVertexAttribute(size_t index, const uint32_t floatAmount, const float* data) const
     *  @brief Set a vertex attribute in the shader.
     *  @param index Index of the attribute to set.
     *  @param floatAmount Amount of floats in the attribute.
     *  @param data Data array.
     ***
     *  @fn void Shader::compile()
     *  @brief Compile the shader from the current set source.
     *
     *  Throws a GLSLException on failure with the error message.
     ***/
}
