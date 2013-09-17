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
                void render(const RenderData& renderData);
                void render(const RenderData& renderData, const RenderTarget& target);
                void renderText(const TextData& textData);
                void renderText(const TextData& textData, const RenderTarget& target);
                void setBlendMode(BlendMode mode);
                void setViewport(Viewport& view);
            private:
                void createOrthoProjection(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far, GLfloat* matrix) const;
                std::unordered_map<std::string, std::shared_ptr<OpenGLRenderMode> > renderModes;
                std::weak_ptr<OpenGLRenderMode> currentMode;

                Viewport* viewport;

        };
    }
}
