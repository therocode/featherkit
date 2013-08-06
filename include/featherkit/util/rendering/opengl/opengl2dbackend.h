#pragma once
#include <featherkit/rendering/renderer2dbackend.h>
#include <featherkit/util/rendering/opengl/opengltexture.h>
#include <featherkit/util/rendering/opengl/openglrendermode.h>
#include <featherkit/util/rendering/opengl/opengl.h>
#include <featherkit/fontstash/fontstash.h>
#include <featherkit/rendering/hashedstorage.h>
#include <unordered_map>

using namespace fea;

namespace fea
{
    namespace util
    {
        class OpenGL2DBackend : public Renderer2DBackend
        {
            public:
                OpenGL2DBackend(HashedStorage<std::string, OpenGLTexture>& tm);
                void setup() override;
                void destroy() override;
                void clear() override;
                void preRender() override;
                void render(RenderData renderData) override;
                void postRender() override;
                int32_t addFont(uint8_t* fontData) override;
                void addRenderMode(const std::string& name, RenderMode* newMode) override;
                void setRenderMode(const std::string& mode) override;
                void setClearColour(const glm::vec3& colour) override;
            private:
                virtual void renderText(const TextData& textData) override;
                HashedStorage<std::string, OpenGLTexture>& textures;
                std::unordered_map<std::string, std::shared_ptr<OpenGLRenderMode> > renderModes;
                std::weak_ptr<OpenGLRenderMode> currentMode;

                sth_stash* stash;
        };
    }
}
