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
            void setSource(const std::string& vertSource, const std::string& fragSource);
            void activate() const;
            void deactivate() const;
            void setUniform(size_t index, UniformType type, const void* value) const;
            void setVertexAttribute(size_t index, const uint32_t floatAmount, const float* data) const;
            void compile();
        private:
            GLuint programId;
            std::unordered_map<size_t, GLint> uniformLocations;
            std::unordered_map<size_t, GLint> vertexAttributeLocations;
            std::string vertexSource;
            std::string fragmentSource;
            mutable std::vector<GLint> enabledVertexAttributes;
    };
}
