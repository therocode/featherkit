#include <fea/rendering/subrectquad.hpp>

namespace fea
{
    SubrectQuad::SubrectQuad() : Quad()
    {
    }

    SubrectQuad::SubrectQuad(const glm::vec2& size) : Quad(size)
    {
    }

    void SubrectQuad::setTexture(const Texture& texture)
    {
        Quad::setTexture(texture);
        updateTexCoords();
    }

    void SubrectQuad::setSubrect(const glm::ivec2& subrectStart, const glm::ivec2& subrectEnd)
    {
        mSubrectStart = subrectStart;
        mSubrectEnd = subrectEnd;

        updateTexCoords();
    }

    void SubrectQuad::updateTexCoords()
    {
        if(mTexture)
        {
            auto percentSubrectStart = static_cast<glm::vec2>(mSubrectStart) / static_cast<glm::vec2>(mTexture->getSize());
            auto percentSubrectEnd = static_cast<glm::vec2>(mSubrectEnd) / static_cast<glm::vec2>(mTexture->getSize());

            glm::vec2 texCoordsX = glm::vec2(percentSubrectStart.x, percentSubrectEnd.x) * mHFlip;
            glm::vec2 texCoordsY = glm::vec2(percentSubrectStart.y, percentSubrectEnd.y) * mVFlip;

            mTexCoords =  {texCoordsX[0], texCoordsY[0],
                texCoordsX[0], texCoordsY[1],
                texCoordsX[1], texCoordsY[0],
                texCoordsX[1], texCoordsY[0],
                texCoordsX[0], texCoordsY[1],
                texCoordsX[1], texCoordsY[1]};

            mUniformsDirty = true;
        }
    }
}
