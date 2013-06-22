#pragma once
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <string>
#include <stdexcept>

namespace windbreeze
{
    class ShaderException : public std::runtime_error 
    {
        public:
            ShaderException(const std::string& message) 
                : std::runtime_error(message) { };
    };

    class ShaderLoader
    {
        public:
            GLuint createShader(std::string vertexSource, std::string fragmentSource);
    };
}
