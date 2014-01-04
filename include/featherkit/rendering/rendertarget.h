#pragma once
#include <stdint.h>
#include <glm/glm.hpp>
#include <featherkit/rendering/texture.h>

namespace fea
{
    class Renderer2DBackend;

    class RenderTarget
    {
        public:
            RenderTarget();
            RenderTarget(RenderTarget&& other);
            RenderTarget(const RenderTarget& other) = delete;
            RenderTarget& operator=(RenderTarget&& other);
            GLuint getId() const;
            glm::uvec2 getSize() const;
            const Texture& getTexture() const;
            void create(uint32_t w, uint32_t h, bool smooth = false);
            void destroy();
            ~RenderTarget();
        private:
            GLuint id;
            uint32_t width;
            uint32_t height;
            Texture texture;
    };
    /** @addtogroup Render2D
     *@{
     *  @class RenderTarget
     *@}
     ***
     *  @class RenderTarget
     *  @brief Container class for a render target resource that represents a buffer than can be drawn on and be used as a texture to display it.
     *
     *  RenderTarget instances are tied to the rendering system and cannot be created properly on its own. RenderTargets created using the standard constructor will not be valid. To properly create a RenderTarget, use the Renderer2D::createRenderTarget function. Because RenderTargets represents internal buffers of the rendering system, they cannot be copied.
     *
     *  A RenderTarget instance has to be kept alive as long as they are in use, otherwise it will result in undefined behaviour.
     ***
     *  @fn RenderTarget::RenderTarget()
     *  @brief Construct an uninitialised RenderTarget.
     *
     *  RenderTargets created this way need to be set to a valid RenderTarget returned by the Renderer2D::createRenderTarget function.
     ***
     *  @fn RenderTarget::RenderTarget(RenderTarget&& other)
     *  @brief Move constructor.
     *  @param other Other instance.
     ***
     *  @fn RenderTarget::RenderTarget(const RenderTarget& other) = delete
     *  @brief Deleted copy constructor.
     *  @param other Instance to copy.
     ***
     *  @fn RenderTarget& RenderTarget::operator=(RenderTarget&& other)
     *  @brief Move assignment operator.
     *  @param other Other instance.
     ***
     *  @fn int32_t RenderTarget::getId() const
     *  @brief Get the ID of the internal render target.
     ***
     *  @fn glm::uvec2 RenderTarget::getSize() const
     *  @brief Get the size.
     *  @return The size.
     ***
     *  @fn const Texture& RenderTarget::getTexture() const
     *  @brief Get the texture tied to this RenderTarget.
     * 
     *  Using the Texture returned by this function, the content of the RenderTarget can be displayed on a drawable.
     *  @return The Texture.
     ***
     *  @fn RenderTarget::~RenderTarget()
     *  @brief Destroy a RenderTarget.
     **/
}
