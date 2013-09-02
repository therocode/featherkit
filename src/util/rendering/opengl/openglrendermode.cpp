#include <featherkit/util/rendering/opengl/openglrendermode.h>

namespace fea
{
    namespace util
    {
        GLuint OpenGLRenderMode::getShader() const
        {
            return shaderProgram;
        }
        
        GLint OpenGLRenderMode::getVertexLocation() const
        {
            return vertexLocation;
        }

        GLint OpenGLRenderMode::getTexCoordsLocation() const
        {
            return texCoordsLocation;
        }
    }
}
