#pragma once
#include <featherkit/rendering/renderer2dbackend.h>
#include <featherkit/util/rendering/opengl/opengltexture.h>
#include <featherkit/util/rendering/opengl/opengl.h>
#include <featherkit/fontstash/fontstash.h>
#include <unordered_map>

using namespace fea;

namespace fea
{
    namespace util
    {
        class OpenGL2DBackend : public Renderer2DBackend
        {
            public:
                OpenGL2DBackend(std::unordered_map<std::string, OpenGLTexture>& tm);
                void setup() override;
                void destroy() override;
                void clear() override;
                void preRender() override;
                void render(RenderData renderData) override;
                void postRender() override;
                int32_t addFont(uint8_t* fontData) override;
            private:
                virtual void renderText(const TextData& textData) override;
                std::unordered_map<std::string, OpenGLTexture>& textures;
                GLuint shaderProgram;

                sth_stash* stash;
        };
    }
}
