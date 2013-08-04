#pragma once
#include <featherkit/rendering/renderer2dbackend.h>
#include <featherkit/rendering/viewport.h>
#include <stdexcept>
#include <memory>

namespace fea
{
    class Drawable2D;

    class InvalidFontException : public std::runtime_error 
    {
        public:
            InvalidFontException(const std::string& message);
    };

    class Renderer2D
    {
        public:
            Renderer2D(Renderer2DBackend* b, Viewport v);
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
            void setRenderMode(const std::string& mode);
        private:
            std::unique_ptr<Renderer2DBackend> backend;
            Viewport currentViewport;
            uint32_t clock;
    };
    /** @addtogroup Render2D
     *@{
     *  @class InvalidFontException
     *  @class Renderer2D
     *@}
     ***
     *  @class InvalidFontException
     *  @brief Exception used when something has gone wrong with font handling.
     ***
     *  @fn InvalidFontException::InvalidFontException(const std::string& message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
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
     *  @fn Renderer2D::Renderer2D(Renderer2DBackend* b, Viewport v)
     *  @brief Construct a renderer with the given backend and Viewport.
     *
     *  @param b Backend to store as an std::unique_ptr. The memory will be managed internally.
     *  @param v Viewport to use.
     *** 
     *  @fn void Renderer2D::setup()
     *  @brief Perform one-time setup for the renderer.
     *  
     *  When the renderer is setup, it is ready to be used. The underlying purpose of this function may vary depending on the backend used.
     ***
     *  @fn void Renderer2D::destroy()
     *  @brief Perform destruction of the renderer.
     *
     *  Used after setup has been called and when the renderer is not needed anymore. The underlying purpose of this function may vary depending on the backend used.
     ***
     *  @fn void Renderer2D::clear()
     *  @brief Clear the screen.
     *
     *  Usually used once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     ***
     *  @fn void Renderer2D::preRender()
     *  @brief Prepare the renderer for rendering.
     *
     *  Needs to be called once every frame before the drawables are rendered. If the camera is moved or other settings changed, it has to be called again.
     ***
     *  @fn void Renderer2D::render(const Drawable2D& drawable)
     *  @brief Render the given drawable to the screen.
     *
     *  Can take any object which inherits from the Drawable2D base class. The drawables will be rendered offset and transformed depending on the current Viewport of the renderer.
     *  @param drawable Object to draw to the screen.
     ***
     *  @fn void Renderer2D::postRender()
     *  @brief Finalise the rendering procedure of the current frame.
     *
     *  Call this when all drawables that should be drawn this frame has been drawn. Depending on the backend, nothing may be visible on the screen until this function has been called.
     ***
     *  @fn void Renderer2D::setViewport(const Viewport& viewport)
     *  @brief Set the Viewport of the renderer
     *  @param viewport Viewport to set it to.
     ***
     *  @fn Viewport& Renderer2D::getViewport()
     *  @brief Access the current Viewport.
     *  
     *  Returns a reference, so this can be used to modify the Viewport.
     *  @return A reference to the Viewport.
     ***
     *  @fn void Renderer2D::resize(uint32_t w, uint32_t h)
     *  @brief Change the size of the rendering area.
     *
     *  Necessary to call when the window size has changed.
     *  @param w Width of the new area size.
     *  @param h Height of the new area size.
     ***
     *  @fn int32_t Renderer2D::addFont(uint8_t* fontData)
     *  @brief Add a font to the renderer from memory.
     *  
     *  The font has to be loaded into a char array. That array is then passed to this function. If the font is added correctly, a numerical value which is not zero is returned. Otherwise a InvalidFontException is thrown.
     *
     *  Only ttf fonts are supported.
     *  @param fontData Array with font data.
     *  @return Number representing the font.
     ***/
}
