#pragma once
#include <featherkit/rendering/rendermode.h>
#include <featherkit/util/rendering/opengl/opengl.h>

namespace fea
{
    namespace util
    {
        class OpenGLRenderMode : public RenderMode
        {
            public:
                virtual void setup() override = 0;
                virtual void preRender() override = 0;
                virtual void postRender() override = 0;
                GLuint getShader() const;
            protected:
                GLuint shaderProgram;
        };
    }
}
