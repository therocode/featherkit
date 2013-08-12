#pragma once
#include <featherkit/rendering/quad.h>

namespace fea
{
    class SubrectQuad : public Quad
    {
        public:
            SubrectQuad();
            SubrectQuad(float w, float h);
            SubrectQuad(const glm::vec2& size);
            void setSubrect(float startX, float startY, float endX, float endY);
            void setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
        private:
            glm::vec2 subrectStart;
            glm::vec2 subrectEnd;
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
     *  @fn SubrectQuad::SubrectQuad(float w, float h)
     *  @brief Construct a SubrectQuad with the given size.
     *  
     *  Uses the Quad::Quad(float w, float h) constructor.
     *  @param w Width.
     *  @param h Height.
     ***
     *  @fn SubrectQuad::SubrectQuad(const glm::vec2& size)
     *  @brief Construct a SubrectQuad with the given size.
     *  
     *  Uses the Quad::Quad(const glm::vec2& size) constructor.
     *  @param size Size.
     ***
     *  @fn void SubrectQuad::setSubrect(float startX, float startY, float endX, float endY)
     *  @brief Define which region of the Texture that should be displayed.
     *  
     *  The regions are given in percent of total texture size.
     *  @param startX X coordinate of the top-left corner of the region.
     *  @param startY Y coordinate of the top-left corner of the region.
     *  @param endX X coordinate of the bottom-right corner of the region.
     *  @param endY Y coordinate of the bottom-right corner of the region.
     ***
     *  @fn void SubrectQuad::setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd)
     *  @brief Define which region of the Texture that should be displayed.
     *  
     *  The regions are given in percent of total texture size.
     *  @param srStart Coordinates of the top-left corner of the region.
     *  @param srEnd Coordinates of the bottom-right corner of the region.
     ***
     *  @fn virtual void SubrectQuad::getRenderData(RenderData& renderData, uint32_t time) const override
     *  @brief Overrides Quad::getRenderData.
     *  @param renderData See Quad::getRenderData.
     *  @param time See Quad::getRenderData.
     ***/
}
