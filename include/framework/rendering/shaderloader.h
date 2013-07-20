#pragma once
#include <framework/util/rendering/opengl.h>
#include <string>
#include <stdexcept>

namespace fk
{
    class ShaderException : public std::runtime_error 
    {
        public:
            ShaderException(const std::string& message);
    };

    class ShaderLoader
    {
        public:
            GLuint createShader(std::string vertexSource, std::string fragmentSource);
    };
}
