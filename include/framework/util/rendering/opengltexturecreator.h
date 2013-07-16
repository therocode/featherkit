#pragma once
#include <stdint.h>
#include <framework/util/rendering/opengltexture.h>
#include <framework/util/rendering/opengl.h>

namespace windbreeze
{
    enum ResizeAlgorithm{NEAREST, LINEAR};

    class OpenGLTextureCreator
    {
        public:
            OpenGLTexture createTexture(const unsigned char* pixels, uint32_t width, uint32_t height, ResizeAlgorithm algo = NEAREST) const;
    };
}
