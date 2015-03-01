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
            void setSubrect(const glm::vec2& subrectStart, const glm::vec2& subrectEnd);
            virtual std::vector<RenderEntity> getRenderInfo() const override;
        private:
            glm::vec2 mSubrectStart;
            glm::vec2 mSubrectEnd;
    };
    /** @addtogroup Rendering
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
     *  @fn SubrectQuad::SubrectQuad(const glm::vec2& size)
     *  @brief Construct a SubrectQuad with the given size.
     *  
     *  Uses the Quad::Quad(const glm::vec2& size) constructor.
     *  Assert/undefined behavior if the size is zero or negative in any dimension.
     *  @param size Size.
     ***
     *  @fn void SubrectQuad::setSubrect(const glm::vec2& subrectStart, const glm::vec2& subrectEnd)
     *  @brief Define which region of the Texture that should be displayed.
     *  
     *  The regions are given in percent of total texture size.
     *  @param subrectStart Coordinates of the top-left corner of the region.
     *  @param subrectEnd Coordinates of the bottom-right corner of the region.
     ***/
}
