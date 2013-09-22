#pragma once
#include <featherkit/rendering/viewport.h>
#include <featherkit/rendering/rendertarget.h>
#include <featherkit/rendering/shader.h>
#include <featherkit/rendering/renderinfo.h>
#include <featherkit/fontstash/fontstash.h>
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
            Renderer2D(const Viewport& v);
            void setup();
            void destroy();
            void clear(float r, float g, float b);
            void clear(const glm::vec3& colour = glm::vec3());
            void clear(const RenderTarget& target, float r, float g, float b);
            void clear(const RenderTarget& target, const glm::vec3& colour = glm::vec3());
            void queue(const Drawable2D& drawable);
            void render();
            void render(const RenderTarget& target);
            void render(const Shader& shader);
            void render(const RenderTarget& target, const Shader& shader);
            void setViewport(const Viewport& viewport);
            Viewport& getViewport();
            int32_t addFont(uint8_t* fontData);
            void setBlendMode(BlendMode mode);
        private:
            void setBlendModeGl(BlendMode mode);
            Viewport currentViewport;

            sth_stash* stash;

            Texture defaultTexture;
            Shader defaultShader;
            glm::mat4 projection;

            BlendMode currentBlendMode;
            std::vector<RenderInfo> renderQueue;

            //cache
            glm::vec3 clearColour;
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
     *  @fn void Renderer2D::clear(const RenderTarget& target)
     *  @brief Clear the given RenderTarget.
     *
     *  Usually used once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     *  @param target RenderTarget to clear.
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
     *  @fn void Renderer2D::render(const Drawable2D& drawable, const RenderTarget& target)
     *  @brief Render the given drawable to the given RenderTarget.
     *
     *  Can take any object which inherits from the Drawable2D base class. The drawables will be rendered offset and transformed depending on the current Viewport of the renderer.
     *  @param drawable Object to draw.
     *  @param target RenderTarget to draw on.
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
     *  @fn int32_t Renderer2D::addFont(uint8_t* fontData)
     *  @brief Add a font to the renderer from memory.
     *  
     *  The font has to be loaded into a char array. That array is then passed to this function. If the font is added correctly, a numerical value which is not zero is returned. Otherwise a InvalidFontException is thrown.
     *
     *  Only ttf fonts are supported.
     *  @param fontData Array with font data.
     *  @return Number representing the font.
     ***
     *  @fn void Renderer2D::addRenderMode(const std::string& name, RenderMode* newMode)
     *  @brief Add a render mode.
     *  
     *  A render mode specifies how things are rendered. For example, it could render things textured, or without textures.
     *  @param name Name of the render mode.
     *  @param newMode Pointer to the new mode.
     ***
     *  @fn void Renderer2D::setRenderMode(const std::string& mode)
     *  @brief Set which render mode to use.
     *  @param mode Name of the render mode.
     ***
     *  @fn void Renderer2D::setClearColour(float r, float g, float b)
     *  @brief Set the colour to use for clearing.
     *
     *  Values should be between 0 and 1 where 1 is full colour.  
     *
     *  @param r Red component.
     *  @param g Green component.
     *  @param b Blue component.
     ***
     *  @fn void Renderer2D::setClearColour(const glm::vec3& colour)
     *  @brief Set the colour to use for clearing.
     *
     *  Values should be between 0 and 1 where 1 is full colour.  
     *  
     *  @param colour Colour to set it to.
     ***
     *  @fn void Renderer2D::setBlendMode(BlendMode mode)
     *  @brief Set which blend mode to use.
     *
     *  The blend mode decides how drawables are blended with the background when they are drawn.
     * 
     *  @param mode Blend mode.
     ***
     *  @fn Texture Renderer2D::createTexture(uint32_t w, uint32_t h, const uint8_t* imageData, bool smooth = false)
     *  @brief Create a Texture.
     *
     *  The created Texture can be used by quads. Keep in mind that a Texture has to be stored and kept alive as long as there are quads using it. The function takes a pointer to image data which will be used for the Texture. It has to be raw RGBA pixel data.
     *
     *  @param w Width of the Texture.
     *  @param h Height of the Texture.
     *  @param imageData Pointer to raw image data.
     *  @param smooth Set this to true to make the Texture appear smooth instead of pixellated when scaled. Default is false.
     ***
     *  @fn RenderTarget Renderer2D::createRenderTarget(uint32_t w, uint32_t h, bool smooth = false)
     *  @brief Create a RenderTarget.
     *
     *  The created RenderTarget can be both drawn on and be used as a Texture to display what was drawn on it on a quad. Keep in mind that a RenderTarget has to be stored and kept alive as long as it is being used.
     *  @param w Width of the RenderTarget.
     *  @param h Height of the RenderTarget.
     *  @param smooth Set this to true to make the Texture of the RenderTarget appear smooth instead of pixellated when scaled. Default is false.
     ***/
}
