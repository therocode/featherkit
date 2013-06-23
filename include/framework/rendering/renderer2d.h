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
    /** @addtogroup Render2D
     *@{
     *  @class Renderer2D
     *@}
     ***
     *  @class Renderer2D
     *  @brief Used to render 2D drawables to the screen.
     *
     *  This class provides a complete interface for rendering to the screen. Only objects which inherit from the Drawable2D base class may be rendered.
     *
     *  Rendered drawables provide vertices translated to worldspace to the renderer via the Drawable2D::getVerticesTransformed function. This means that for any custom drawable, this function is meant to return the vertex coordinates in world space. 
     *
     *  The Renderer2D keeps a Viewport describing the size of the render area as well as the current camera data.
     *
     *  The functions Renderer2D::preRender and Renderer2D::postRender must be called every frame surrounding all calls to Renderer2D::render. Otherwise rendering may not function properly. 
     *
     *  A backend must be given upon construction. The backend is an implementation of the abstract class Renderer2DBackend. This is the one actually doing the rendering and may be implemented using various rendering methods.
     ***
     *  @fn Renderer2D::Renderer2D(Renderer2DBackend& b, Viewport v)
     *  @brief Construct a renderer with the given backend and Viewport.
     *
     *  Blabla 
     *
     *  @param b ID of the new entity.
     *  @param v EntityManager that the entity will use.
     ***/
}
