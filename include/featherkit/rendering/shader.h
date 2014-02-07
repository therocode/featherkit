#pragma once
#include <featherkit/rendering/uniform.h>
#include <featherkit/rendering/vertexattribute.h>
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
}
