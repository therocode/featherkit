#include <featherkit/util/rendering/opengl/openglrendermode.h>

namespace fea
{
    namespace util
    {
        void OpenGLRenderMode::cacheUniforms()
        {
            glUseProgram(shaderProgram);
            vertexLocation = glGetAttribLocation(shaderProgram, "vertex");
            texCoordsLocation = glGetAttribLocation(shaderProgram, "texCoords");
            projectionLocation = glGetUniformLocation(shaderProgram, "projection");

            positionUniform = glGetUniformLocation(shaderProgram, "position");
            zoomUniform = glGetUniformLocation(shaderProgram, "zoom");
            rotationUniform = glGetUniformLocation(shaderProgram, "rotation");
            halfSizeUniform = glGetUniformLocation(shaderProgram, "halfViewSize");
            constrainXUniform = glGetUniformLocation(shaderProgram, "constrainX");
            constrainYUniform = glGetUniformLocation(shaderProgram, "constrainY");
            textureScroll = glGetUniformLocation(shaderProgram, "textureScroll");
            parallax = glGetUniformLocation(shaderProgram, "parallax");
            colour = glGetUniformLocation(shaderProgram, "colour");
            opacity = glGetUniformLocation(shaderProgram, "opacity");
        }
        
        void OpenGLRenderMode::updateProjection(float* matrix) const
        {
            glUseProgram(shaderProgram);
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, matrix);
        }
    }
}
