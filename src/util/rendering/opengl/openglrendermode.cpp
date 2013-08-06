#include <featherkit/util/rendering/opengl/openglrendermode.h>

namespace fea
{
    namespace util
    {
        GLuint OpenGLRenderMode::getShader() const
        {
            return shaderProgram;
        }
    }
}
