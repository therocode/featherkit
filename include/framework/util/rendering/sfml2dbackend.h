#pragma once
#include <framework/rendering/renderer2dbackend.h>
#include <framework/util/rendering/opengltexture.h>
#include <framework/rendering/texturemanager.h>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <framework/fontstash/fontstash.h>

namespace windbreeze
{
    class Sfml2DBackend : public Renderer2DBackend
    {
        public:
            Sfml2DBackend(TextureManager<OpenGLTexture>& tm) : textureManager(tm) {}
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
            GLuint shaderProgram = 0;

            sth_stash* stash;
    };
}
