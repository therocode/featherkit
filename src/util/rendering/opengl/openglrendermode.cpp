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
        
        void OpenGLRenderMode::updateProjection(float* matrix) const
        {
            glUseProgram(shaderProgram);
            GLint projectionLocation = glGetUniformLocation(shaderProgram, "projection");
            glUniformMatrix4fv(projectionLocation, 1, true, matrix);
        }
    }
}
