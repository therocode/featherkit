#pragma once
#include <featherkit/util/rendering/opengl/openglrendermode.h>

namespace fea
{
    namespace util
    {
        class PlainMode : public OpenGLRenderMode
        {
            virtual void setup() override;
            virtual void preRender() override;
            virtual void postRender() override;
        };
    }
}
