#pragma once
#include <featherkit/rendering/viewport.h>
#include <featherkit/rendering/rendertarget.h>
#include <featherkit/rendering/shader.h>
#include <featherkit/rendering/renderinfo.h>
#include <memory>

namespace fea
{
    class Drawable2D;

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
            void setBlendMode(BlendMode mode);
        private:
            void setBlendModeGl(BlendMode mode);
            Viewport currentViewport;

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
     *  @fn Renderer2D::Renderer2D(Viewport v)
     *  @brief Construct a renderer with the given Viewport.
     *
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
     *  @fn void Renderer2D::clear(float r, float g, float b)
     *  @brief Clear the screen, filling it with the given colour.
     *
     *  Usually called once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     *  @param r Red component. Given in the range of 0 to 1.
     *  @param g Red component. Given in the range of 0 to 1.
     *  @param b Red component. Given in the range of 0 to 1.
     ***
     *  @fn void Renderer2D::clear(const glm::vec3& colour = glm::vec3())
     *  @brief Clear the screen, filling it with the given colour.
     *
     *  Usually called once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     *  @param colour Vector containing colour components. Given in the range of 0 to 1.
     ***
     *  @fn void Renderer2D::clear(const RenderTarget& target, float r, float g, float b)
     *  @brief Clear the given RenderTarget, filling it with the given colour.
     *
     *  Usually called once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     *  @param target RenderTarget to clear.
     *  @param r Red component. Given in the range of 0 to 1.
     *  @param g Red component. Given in the range of 0 to 1.
     *  @param b Red component. Given in the range of 0 to 1.
     ***
     *  @fn void Renderer2D::clear(const RenderTarget& target, const glm::vec3& colour = glm::vec3())
     *  @brief Clear the given RenderTarget, filling it with the given colour.
     *
     *  Usually called once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     *  @param target RenderTarget to clear.
     *  @param colour Vector containing colour components. Given in the range of 0 to 1.
     ***
     *  @fn void Renderer2D::queue(const Drawable2D& drawable)
     *  @brief Queue a drawable for rendering.
     *
     *  Can take any object which inherits from the Drawable2D base class. The drawable will be rendered offset and transformed depending on the current Viewport of the renderer.
     *
     *  @param drawable Object to queue.
     ***
     *  @fn void Renderer2D::render()
     *  @brief Render all queued drawables to the screen.
     ***
     *  @fn void Renderer2D::render(const RenderTarget& target)
     *  @brief Render all queued drawables to a RenderTarget.
     *
     *  @param target RenderTarget to render to.
     ***
     *  @fn void Renderer2D::render(const Shader& shader)
     *  @brief Render all queued drawables using a custom shader.
     *
     *  @param shader Shader object to use.
     ***
     *  @fn void Renderer2D::render(const RenderTarget& target, const Shader& shader)
     *  @brief Render all queued drawables to a RenderTarget using a custom shader.
     *
     *  @param target RenderTarget to render to.
     *  @param shader Shader object to use.
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
     *  @fn void Renderer2D::setBlendMode(BlendMode mode)
     *  @brief Set which blend mode to use.
     *
     *  The blend mode decides how drawables are blended with the background when they are drawn.
     * 
     *  @param mode Blend mode.
     ***/
}
