#include <featherkit/util/rendering/opengl/opengltexturecreator.h>

namespace fku
{
    OpenGLTexture OpenGLTextureCreator::createTexture(const unsigned char* pixels, uint32_t width, uint32_t height, ResizeAlgorithm algo) const
    {
        OpenGLTexture texture;

        GLuint id;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        if(algo == NEAREST)
        {
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        }
        else if(algo == LINEAR)
        {
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        texture.glId = id;

        return texture;
    }
}
