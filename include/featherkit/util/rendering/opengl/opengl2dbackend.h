#pragma once
#include <featherkit/rendering/renderer2dbackend.h>
#include <featherkit/util/rendering/opengl/openglrendermode.h>
#include <featherkit/util/rendering/opengl/opengl.h>
#include <featherkit/fontstash/fontstash.h>
#include <unordered_map>
#include <memory>

namespace fea
{
    namespace util
    {
        class OpenGL2DBackend : public Renderer2DBackend
        {
            public:
                OpenGL2DBackend();
                void setup() override;
                void destroy() override;
                void clear() override;
                void clear(const RenderTarget& target) override;
                void preRender() override;
                void render(const RenderData& renderData) override;
                void render(const RenderData& renderData, const RenderTarget& target) override;
                void renderText(const TextData& textData) override;
                void renderText(const TextData& textData, const RenderTarget& target) override;
                void postRender() override;
                int32_t addFont(uint8_t* fontData) override;
                void addRenderMode(const std::string& name, RenderMode* newMode) override;
                void setRenderMode(const std::string& mode) override;
                void setClearColour(const glm::vec3& colour) override;
                void setBlendMode(BlendMode mode) override;
                void setViewport(Viewport& view) override;
                Texture createTexture(uint32_t w, uint32_t h, const uint8_t* imageData, bool smooth = false) override;
                void destroyTexture(int32_t id) override;
                RenderTarget createRenderTarget(uint32_t w, uint32_t h, bool smooth = false) override;
                void destroyRenderTarget(int32_t id) override;
            private:
                std::unordered_map<int32_t, GLuint> textures;
                int32_t nextTextureId;
                std::unordered_map<int32_t, GLuint> renderTargets;
                int32_t nextRenderTargetId;
                std::unordered_map<std::string, std::shared_ptr<OpenGLRenderMode> > renderModes;
                std::weak_ptr<OpenGLRenderMode> currentMode;

                Viewport* viewport;

                sth_stash* stash;
        };
    }
}
