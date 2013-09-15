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
            private:
                void createOrthoProjection(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far, GLfloat* matrix) const;
                std::unordered_map<std::string, std::shared_ptr<OpenGLRenderMode> > renderModes;
                std::weak_ptr<OpenGLRenderMode> currentMode;

                Viewport* viewport;

                sth_stash* stash;

                Texture defaultTexture;
        };
    }
}
