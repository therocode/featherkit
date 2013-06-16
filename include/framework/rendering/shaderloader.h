#pragma once
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <string>

namespace windbreeze
{
    class ShaderLoader
    {
        public:
            GLuint createShader(std::string vertexSource, std::string fragmentSource);
    };
}
