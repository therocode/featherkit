#pragma once
#include <stdint.h>
#include <glm/glm.hpp>
#include <featherkit/rendering/texture.hpp>

namespace fea
{
    class RenderTarget
    {
        public:
            RenderTarget();
            RenderTarget(RenderTarget&& other);
            RenderTarget(const RenderTarget& other) = delete;
            RenderTarget& operator=(RenderTarget&& other);
            RenderTarget& operator=(const RenderTarget& other) = delete;
            GLuint getId() const;
            glm::uvec2 getSize() const;
            const Texture& getTexture() const;
            void create(uint32_t width, uint32_t height, bool smooth = false);
            void destroy();
            ~RenderTarget();
        private:
            GLuint mId;
            uint32_t mWidth;
            uint32_t mHeight;
            Texture mTexture;
    };
    /** @addtogroup Render2D
     *@{
     *  @class RenderTarget
     *@}
     ***
     *  @class RenderTarget
     *  @brief Container class for a render target resource that represents a buffer than can be drawn on and be used as a texture to display it.
     *
     *  Because RenderTargets represents internal buffers of the rendering system, they cannot be copied.
     *
     *  A RenderTarget instance has to be kept alive as long as they are in use.
     ***
     *  @fn RenderTarget::RenderTarget()
     *  @brief Construct an uninitialised RenderTarget.
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
     *  @fn RenderTarget& RenderTarget::operator=(const RenderTarget& other)
     *  @brief Deleted assignment operator.
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
     *  @fn void RenderTarget::create(uint32_t width, uint32_t height, bool smooth = false)
     *  @brief Create a RenderTarget with the given size.
     *
     *  This method has to be called prior to using the RenderTarget. 
     *  Assert/undefined behavior if size is zero or less in any dimension.
     *  @param width Width of the RenderTarget.
     *  @param height Height of the RenderTarget.
     *  @param smooth If this is true, the internal texture used by the RenderTarget will be smoothed using a nearest neighbor algorithm.
     ***
     *  @fn void RenderTarget::destroy()
     *  @brief Release the resources in use by the RenderTarget.
     ***
     *  @fn RenderTarget::~RenderTarget()
     *  @brief Destroy a RenderTarget.
     **/
}
