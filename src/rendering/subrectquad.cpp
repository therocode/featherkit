#include <featherkit/rendering/subrectquad.h>

namespace fea
{
    SubrectQuad::SubrectQuad() : Quad(), mSubrectEnd(1.0f, 1.0f)
    {
    }

    SubrectQuad::SubrectQuad(const glm::vec2& size) : Quad(size), mSubrectEnd(1.0f, 1.0f)
    {
    }

    void SubrectQuad::setSubrect(const glm::vec2& subrectStart, const glm::vec2& subrectEnd)
    {
        mSubrectStart = subrectStart;
        mSubrectEnd = subrectEnd;

        glm::vec2 texCoordsX = glm::vec2(mSubrectStart.x, mSubrectEnd.x) * mHFlip;
        glm::vec2 texCoordsY = glm::vec2(mSubrectStart.y, mSubrectEnd.y) * mVFlip;

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};
    }

    RenderInfo SubrectQuad::getRenderInfo() const
    {
        RenderInfo temp = Quad::getRenderInfo();
        std::hash<std::string> stringHasher;

        temp.mVertexAttributes.push_back(VertexAttribute(stringHasher("texCoords"), 2, &mTexCoords[0]));

        return temp;
    }
}
