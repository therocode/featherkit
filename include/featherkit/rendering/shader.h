#pragma once

namespace fea
{
    class Shader
    {
        public:
            void setSource(const std::string& vertSource, const std::string& fragSource);
            void activate();
            void deactivate();
            void setUniform(uint32_t index, Uniform::Type type, void* value);
            void setVertexAttribute(uint32_t index, float* data);
            void compile();
        private:
            GLuint programId;
            std::unordered_map<size_t, GLint> uniformLocations;
            std::unordered_map<size_t, GLint> vertexAttributeLocations;
            std::string vertexSource;
            std::String fragmentSource;
    };
}
