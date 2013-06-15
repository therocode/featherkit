#pragma once
#include <framework/rendering/renderer2dbackend.h>
#include <framework/rendering/viewport.h>

namespace windbreeze
{
    class Drawable2D;

    class Renderer2D
    {
        public:
            Renderer2D(Renderer2DBackend& b, Viewport v);
            void setup();
            void destroy();
            void clear();
            void preRender();
            void render(const Drawable2D& drawable);
            void postRender();
            void setViewport(const Viewport& viewport);
            Viewport& getViewport();
        private:
            Renderer2DBackend& backend;
            Viewport currentViewport;
            uint32_t clock = 0;
    };
}
