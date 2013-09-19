#pragma once
#include <featherkit/rendering/animatedquad.h>

namespace fea
{
    class RepeatedQuad : public AnimatedQuad
    {
        public:
            RepeatedQuad();
            RepeatedQuad(float w, float h);
            RepeatedQuad(const glm::vec2& size);
            void setTileSize(float w, float h);
            void setTileSize(const glm::vec2& size);
            const glm::vec2& getTileSize();
            void setScrollSpeed(const glm::vec2& speed);
            void setScrollSpeed(float w, float h);
            const glm::vec2& getScrollSpeed() const;
            virtual RenderInfo getRenderInfo() const override;
        private:
            glm::vec2 tileSize;
            glm::vec2 scrollSpeed;
            glm::vec2 currentScroll;
    };
    /** @addtogroup Render2D
     *@{
     *  @class RepeatedQuad
     *@}
     ***
     *  @class RepeatedQuad
     *  @brief An AnimatedQuad which texture is capable of wrapping.
     *
     *  The purpose of texture wrapping is to create a repeated surface. With a tiling texture, this can be used to create several effects such as a rain overlay, cloud background or similar. It acts in the same was as a normal AnimatedQuad except that instead of streching the texture when it is enlarged, the texture is wrapped.
     ***
     *  @fn RepeatedQuad::RepeatedQuad()
     *  @brief Construct a RepeatedQuad.
     *
     *  Uses the AnimatedQuad::AnimatedQuad() constructor.
     ***
     *  @fn RepeatedQuad::RepeatedQuad(float w, float h)
     *  @brief Construct a RepeatedQuad with a specific size.
     *
     *  Uses the AnimatedQuad::AnimatedQuad(float w, float h) constructor.
     *  @param w Width.
     *  @param h Height.
     ***
     *  @fn RepeatedQuad::RepeatedQuad(const glm::vec2& size)
     *  @brief Construct a RepeatedQuad with a specific size.
     *
     *  Uses the AnimatedQuad::AnimatedQuad(const glm::vec2& size) constructor.
     *  @param size Size.
     ***
     *  @fn void RepeatedQuad::setTileSize(const glm::vec2& size)
     *  @brief Set the size of every repeated texture cell.
     *  @param size Vector containing the size.
     ***
     *  @fn void RepeatedQuad::setTileSize(float w, float h)
     *  @brief Set the size of every repeated texture cell.
     *  @param w Tile width.
     *  @param h Tile height.
     ***
     *  @fn const glm::vec2& RepeatedQuad::getTileSize()
     *  @brief Get the texture cell size.
     ***
     *  @fn void RepeatedQuad::setScrollSpeed(const glm::vec2& speed)
     *  @brief Set the rate at which the texture is scrolled.
     *
     *  Texture scrolling makes the wrapped texture image glide over the RepeatedQuad. Can be used to make clouds moving in the wind or a scrolling space background for instance.
     *  @param speed Vector containing the rate of which the texture scrolls.
     ***
     *  @fn void RepeatedQuad::setScrollSpeed(float x, float y)
     *  @brief Set the rate at which the texture is scrolled.
     *
     *  Texture scrolling makes the wrapped texture image glide over the RepeatedQuad. Can be used to make clouds moving in the wind or a scrolling space background for instance.
     *  @param x Speed of the scrolling along the X axis.
     *  @param y Speed of the scrolling along the Y axis.
     ***
     *  @fn const glm::vec2& RepeatedQuad::getScrollSpeed() const
     *  @brief Get the rate at which the texture is scrolled.
     *  @return Vector containing the scroll speed.
     ***
     *  @fn virtual void RepeatedQuad::getRenderData(RenderData& renderData, uint32_t time) const override
     *  @brief Overrides AnimatedQuad::getRenderData.
     *  @param renderData See AnimatedQuad::getRenderData.
     *  @param time See AnimatedQuad::getRenderData.
     **/
}
