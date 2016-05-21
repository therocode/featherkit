#pragma once
#include <fea/config.hpp>
#include <fea/rendering/color.hpp>
#include <fea/rendering/viewport.hpp>
#include <fea/rendering/rendertarget.hpp>
#include <fea/rendering/shader.hpp>
#include <fea/rendering/renderentity.hpp>
#include <memory>

namespace fea
{
    class Drawable2D;

    class FEA_API Renderer2D
    {
        public:
            Renderer2D(const Viewport& viewport);
            void clear(const Color& color = Color());
            void clear(const RenderTarget& target, const Color& color = Color());
            template<typename Drawable>
            void render(const Drawable& drawable);
            template<typename Drawable>
            void render(const Drawable& drawable, const RenderTarget& target);
            template<typename Drawable>
            void render(const Drawable& drawable, Shader& shader);
            template<typename Drawable>
            void render(const Drawable& drawable, const RenderTarget& target, Shader& shader);
            void setViewport(const Viewport& viewport);
            const Viewport& getViewport() const;
            Viewport& getViewport();
            void setBlendMode(BlendMode mode);
        private:
            void setBlendModeGl(BlendMode mode);
            Viewport mCurrentViewport;

            Texture mDefaultTexture;
            GLuint mVertexArray;
            Shader mDefaultShader;
            glm::mat4 mProjection;

            BlendMode mCurrentBlendMode;

            //cache
            Color mClearColor;
    };

#include <fea/rendering/renderer2d.inl>
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
     *  This class provides a complete interface for rendering to the screen.
     *
     *  The Renderer2D keeps a Viewport describing the size of the render area as well as the current camera data.
     *
     *  Important: A valid OpenGL context must exist to be able to construct the renderer.
     ***
     *  @fn Renderer2D::Renderer2D(Viewport viewport)
     *  @brief Construct a renderer with the given Viewport.
     *
     *  @param viewport Viewport to use.
     *** 
     *  @fn void Renderer2D::clear(const Color& color = Color())
     *  @brief Clear the screen, filling it with the given color.
     *
     *  Usually called once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     *  @param color Color object. Black by default.
     ***
     *  @fn void Renderer2D::clear(const RenderTarget& target, const Color& = Color())
     *  @brief Clear the given RenderTarget, filling it with the given color. 
     *
     *  Usually called once every frame as a first step of the rendering process to clear out what was drawn the last frame.
     *  @param target RenderTarget to clear.
     *  @param color Color object. Black by default.
     ***
     *  @fn void Renderer2D::render(const Drawable& drawable)
     *  @brief Render drawable to the screen.
     *
     *  Can take any object which implements a public method getRenderInfo which returns an iterable container of RenderEntity objects. The Drawable2D class fits this criteria. The drawable will be rendered offset and transformed depending on the current Viewport of the renderer.
     *  @param drawable Drawable to render.
     ***
     *  @fn void Renderer2D::render(const Drawable& drawable, const RenderTarget& target)
     *  @brief Render drawable to a RenderTarget.
     *
     *  @param drawable Drawable to render.
     *  @param target RenderTarget to render to.
     ***
     *  @fn void Renderer2D::render(const Drawable& drawable, Shader& shader)
     *  @brief Render drawable using a custom shader.
     *
     *  @param drawable Drawable to render.
     *  @param shader Shader object to use.
     ***
     *  @fn void Renderer2D::render(const Drawable& drawable, const RenderTarget& target, Shader& shader)
     *  @brief Render drawable to a RenderTarget using a custom shader.
     *
     *  @param drawable Drawable to render.
     *  @param target RenderTarget to render to.
     *  @param shader Shader object to use.
     ***
     *  @fn void Renderer2D::setViewport(const Viewport& viewport)
     *  @brief Set the Viewport of the renderer
     *  @param viewport Viewport to set it to.
     ***
     *  @fn const Viewport& Renderer2D::getViewport() const
     *  @brief Access the current Viewport.
     *  
     *  Returns a reference, so this can be used to modify the Viewport.
     *  @return A reference to the Viewport.
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
