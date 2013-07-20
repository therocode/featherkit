#pragma once
#include <framework/rendering/renderer2dbackend.h>
#include <framework/util/rendering/opengltexture.h>
#include <framework/rendering/texturemanager.h>
#include <framework/util/rendering/opengl.h>
#include <framework/fontstash/fontstash.h>

namespace windbreeze
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
