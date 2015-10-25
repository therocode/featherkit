#pragma once
#include <fea/config.hpp>
#include <fea/rendering/quad.hpp>

namespace fea
{
    class FEA_API SubrectQuad : public Quad
    {
        public:
            SubrectQuad();
            SubrectQuad(const glm::vec2& size);
            virtual void setTexture(const Texture& texture) override;
            void setSubrect(const glm::ivec2& subrectStart, const glm::ivec2& subrectEnd);
            virtual std::vector<RenderEntity> getRenderInfo() const override;
        private:
            void updateTexCoords();
            glm::ivec2 mSubrectStart;
            glm::ivec2 mSubrectEnd;
    };
    /** @addtogroup Render2D
     *@{
     *  @class SubrectQuad
     *@}
     ***
     *  @class SubrectQuad
     *  @brief A Quad which can display a subregion of its Texture.
     ***
     *  @fn SubrectQuad::SubrectQuad()
     *  @brief Construct a SubrectQuad.
     *  
     *  Uses the Quad::Quad() constructor.
     ***
     *  @fn void SubrectQuad::setTexture(const Texture& texture)
     *  @brief Set the texture.
     *  @param texture Texture to set.
     ***
     *  @fn SubrectQuad::SubrectQuad(const glm::vec2& size)
     *  @brief Construct a SubrectQuad with the given size.
     *  
     *  Uses the Quad::Quad(const glm::vec2& size) constructor.
     *  Assert/undefined behavior if the size is zero or negative in any dimension.
     *  @param size Size.
     ***
     *  @fn void SubrectQuad::setSubrect(const glm::ivec2& subrectStart, const glm::ivec2& subrectEnd)
     *  @brief Define which region of the Texture that should be displayed.
     *  
     *  The regions are given in pixels.
     *  @param subrectStart Coordinates of the top-left corner of the region.
     *  @param subrectEnd Coordinates of the bottom-right corner of the region.
     ***/
}
