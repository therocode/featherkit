#pragma once
#include <framework/rendering/renderer2dbackend.h>
#include <framework/util/rendering/opengltexture.h>
#include <framework/rendering/texturemanager.h>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

namespace windbreeze
{
    class Sfml2DBackend : public Renderer2DBackend
    {
        public:
            Sfml2DBackend(TextureManager<OpenGLTexture>& tm) : textureManager(tm) {}
            void setup() override;
            void destroy() override;
            void clear() override;
            void render(RenderData renderData) override;
        private:
            TextureManager<OpenGLTexture>& textureManager;
            GLuint shaderProgram = 0;
    };
}
