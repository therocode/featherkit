#include <framework/rendering/subrectquad.h>

namespace windbreeze
{
    void SubrectQuad::setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd)
    {
        subrectStart = srStart;
        subrectEnd = srEnd;
    }

    void SubrectQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Quad::getRenderData(renderData, time);

        glm::vec2 texCoordsX = glm::vec2(subrectStart.x, subrectEnd.x) * hFlip;
        glm::vec2 texCoordsY = glm::vec2(subrectStart.y, subrectEnd.y) * vFlip;

        renderData.texCoords =  {texCoordsX[0], texCoordsY[0],
                                 texCoordsX[0], texCoordsY[1],
                                 texCoordsX[1], texCoordsY[1],
                                 texCoordsX[1], texCoordsY[0]};
    }
}
