#pragma once
#include <vector>
#include <framework/glm/glm.hpp>
#include <framework/rendering/viewport.h>
#include <framework/rendering/renderdata.h>

namespace windbreeze
{
    class Renderer2DBackend
    {
        public:
            virtual void setup() = 0;
            virtual void destroy() = 0;
            virtual void clear() = 0;
            virtual void preRender() = 0;
            virtual void render(RenderData renderData) = 0;
            virtual void postRender() = 0;
            void setViewport(const Viewport& v);
            virtual void renderText(const TextData& textData) = 0;
        protected:
            Viewport viewport;
    };
}
