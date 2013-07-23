#pragma once

namespace fea
{
    namespace util
    {
        struct OpenGLTexture
        {
            uint32_t glId = 0;
        };
        /** @addtogroup Render2D
         *@{
         *  @struct OpenGLTexture
         *@}
         ***
         *  @struct OpenGLTexture
         *  @brief Contains an ID of an OpenGL texture to be used with the OpenGL2DBackend.
         ***
         *  @var OpenGLTexture::glId
         *  @brief Numerical ID of the texture.
         ***/
    }
}
