#pragma once
#include <stdint.h>
#include <featherkit/util/rendering/opengl/opengltexture.h>
#include <featherkit/util/rendering/opengl/opengl.h>

namespace fku
{
    enum ResizeAlgorithm{NEAREST, LINEAR};

    class OpenGLTextureCreator
    {
        public:
            OpenGLTexture createTexture(const unsigned char* pixels, uint32_t width, uint32_t height, ResizeAlgorithm algo = NEAREST) const;
    };
    /** @addtogroup Render2D
     *@{
     *  @class OpenGLTextureCreator
     *@}
     ***
     *  @class OpenGLTextureCreator
     *  @brief Helper class to create OpenGL textures.
     ***
     *  @fn OpenGLTexture OpenGLTextureCreator::createTexture(const unsigned char* pixels, uint32_t width, uint32_t height, ResizeAlgorithm algo = NEAREST) const
     *  @brief Create an OpenGL texture.
     *  
     *  This will create a valid OpenGL texture which can be used for rendering. The returned OpenGLTexture contains the handle to the created texture. 
     *  @param pixels Pointer to raw pixel data representing the image to create the texture out of.
     *  @param width Width of the image in pixels.
     *  @param height Height of the image in pixels.
     *  @param algo Resize algorithm that OpenGL will use for its mipmap representations. Using LINEAR, the images will look smoothed when zoomed. With NEAREST they will have a pixelated look.
     *  @return The handle to the texture wrapped in an OpenGLTexture.
     ***/
}
