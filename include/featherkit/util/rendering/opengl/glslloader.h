#pragma once
#include <featherkit/util/rendering/opengl/opengl.h>
#include <string>
#include <stdexcept>

namespace fea
{
    class GLSLException : public std::runtime_error 
    {
        public:
            GLSLException(const std::string& message);
    };

    class GLSLLoader
    {
        public:
            GLuint createShader(std::string vertexSource, std::string fragmentSource);
    };
}
