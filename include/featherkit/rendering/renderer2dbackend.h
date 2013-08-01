#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <featherkit/rendering/viewport.h>
#include <featherkit/rendering/renderdata.h>

namespace fea
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
            virtual int32_t addFont(uint8_t* fontData) = 0;
        protected:
            Viewport viewport;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Renderer2DBackend
     *@}
     ***
     *  @class Renderer2DBackend
     *  @brief Base class for 2D rendering implementations.
     *
     *  The Renderer2D class relies on an imlpementation of the Renderer2DBackend class to render, and everything rendered will be rendered by the backend.
     *
     *  The rendering is handled by a backend to offer a way to select how the rendering is done. Different backends may implement it differently. For instance, there may be an OpenGL backend or a Direct3D backend.
     ***
     *  @fn virtual void Renderer2DBackend::setup() = 0
     *  @brief Setup the backend.
     *
     *  This function is called by the Renderer2D::setup function and the implementation should contain all one-time setup procedures needed before rendering is started.
     ***
     *  @fn virtual void Renderer2DBackend::destroy() = 0
     *  @brief Destroy the backend.
     *  
     *  This function is called by the Renderer2D::destroy function and the implementation should contain the destruction of resources acquired within the Renderer2DBackend::setup function.
     ***
     *  @fn virtual void Renderer2DBackend::clear() = 0
     *  @brief Clear what has been drawn to the screen.
     *  
     *  This function is called by the Renderer2D::clear function and should clear the screen.
     ***
     *  @fn virtual void Renderer2DBackend::preRender() = 0
     *  @brief Prepare the renderer for the next frame.
     *  
     *  This function is called by the Renderer2D::preRender function typically once every frame before anything is rendered. The implementation should contain everything needed to prepare the renderer for the upcoming frame.
     ***
     *  @fn virtual void Renderer2DBackend::render(RenderData renderData) = 0
     *  @brief Render an object.
     *
     *  This function is called by the Renderer2D class when something needs to be rendered. The RenderData argument contains all needed information to render the object. The object drawn should be transformed accordingly with the Camera.
     *  @param renderData Information on the object to be rendered.
     ***
     *  @fn virtual void Renderer2DBackend::postRender() = 0
     *  @brief Finish the current frame's rendering.
     *
     *  This function is called by the Renderer2D::postRender function typically at the end of every frame, after all things are rendered. The implementation should contain everything needed to finalise the rendering.
     ***
     *  @fn void Renderer2DBackend::setViewport(const Viewport& v)
     *  @brief Set the Viewport.
     *  
     *  This function is automatically called by the Renderer2D::setViewport function.
     *  @param v Viewport to set.
     ***
     *  @fn virtual void Renderer2DBackend::renderText(const TextData& textData) = 0
     *  @brief Render a text object.
     *  
     *  Called by Renderer2D when a text object needs to be rendered. The TextData argument contains information about the text and its location. The text should be transformed by the camera, but not rotated.
     ***
     *  @fn virtual int32_t Renderer2DBackend::addFont(uint8_t* fontData) = 0
     *  @brief Add a fond to the backend.
     *
     *  This function is called by the Renderer2D::addFont function. After this function is called, there should be a valid font to use which is tied to the returned number.
     *  @param fontData Array containing the font data.
     *  @return A numerical value representing the font. Should return 0 if the function fails.
     ***
     *  @var Renderer2DBackend::viewport 
     *  @brief Current Viewport in use. Set using Renderer2DBackend::setViewport.
     ***/
}
