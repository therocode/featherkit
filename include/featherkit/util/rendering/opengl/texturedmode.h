#pragma once
#include <featherkit/util/rendering/opengl/openglrendermode.h>

namespace fea
{
    namespace util
    {
        class TexturedMode : public OpenGLRenderMode
        {
            virtual void setup() override;
            virtual void preRender() override;
            virtual void postRender() override;
            private:
            GLint textureUniform;
        };
    }
}
