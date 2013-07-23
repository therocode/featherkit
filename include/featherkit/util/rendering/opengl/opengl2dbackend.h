#pragma once
#include <featherkit/rendering/renderer2dbackend.h>
#include <featherkit/util/rendering/opengl/opengltexture.h>
#include <featherkit/rendering/texturemanager.h>
#include <featherkit/util/rendering/opengl/opengl.h>
#include <featherkit/fontstash/fontstash.h>

using namespace fea;

namespace fea
{
    namespace util
    {
        class OpenGL2DBackend : public Renderer2DBackend
        {
            public:
                OpenGL2DBackend(TextureManager<OpenGLTexture>& tm);
                void setup() override;
                void destroy() override;
                void clear() override;
                void preRender() override;
                void render(RenderData renderData) override;
                void postRender() override;
                int32_t addFont(uint8_t* fontData) override;
            private:
                virtual void renderText(const TextData& textData) override;
                TextureManager<OpenGLTexture>& textureManager;
                GLuint shaderProgram;

                sth_stash* stash;
        };
    }
}
