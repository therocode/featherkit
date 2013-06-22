#pragma once
#include <framework/rendering/renderer2dbackend.h>
#include <framework/rendering/viewport.h>
#include <stdexcept>

namespace windbreeze
{
    class Drawable2D;

    class InvalidFontException : public std::runtime_error 
    {
        public:
            InvalidFontException(const std::string& message) 
                : std::runtime_error(message) { };
    };

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
            void resize(uint32_t w, uint32_t h);
            int32_t addFont(uint8_t* fontData);
        private:
            Renderer2DBackend& backend;
            Viewport currentViewport;
            uint32_t clock = 0;
    };
}
