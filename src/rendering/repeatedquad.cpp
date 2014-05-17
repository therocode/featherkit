#include <fea/rendering/repeatedquad.hpp>
#include <fea/assert.hpp>

namespace fea
{
    RepeatedQuad::RepeatedQuad() : AnimatedQuad() 
    {
        mTileSize = getSize();
        updateConstraints();
    }

    RepeatedQuad::RepeatedQuad(const glm::vec2& size) : AnimatedQuad(size)
    {
        mTileSize = getSize();
        updateConstraints();
    }

    void RepeatedQuad::setSize(const glm::vec2& size)
    {
        Quad::setSize(size);
        updateConstraints();
    }

    void RepeatedQuad::setTileSize(const glm::vec2& size)
    {
        FEA_ASSERT(size.x > 0.0f && size.y > 0.0f, "Size must be greater than zero in all dimensions when calling RepeatedQuad::setTileSize! " + std::to_string(size.x) + " " + std::to_string(size.y) + " provided.");
        mTileSize = size;
        updateConstraints();
    }

    const glm::vec2& RepeatedQuad::getTileSize()
    {
        return mTileSize;
    }
    
    void RepeatedQuad::setScrollSpeed(const glm::vec2& speed)
    {
        mScrollSpeed = speed;
    }

    const glm::vec2& RepeatedQuad::getScrollSpeed() const
    {
        return mScrollSpeed;
    }
    
    void RepeatedQuad::updateConstraints()
    {
        glm::vec2 hej = getSize() / mTileSize;

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * mHFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * mVFlip;

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        for(uint32_t i = 0; i < 12; i += 2)
        {
            glm::vec2 newCoords = glm::vec2(mTexCoords[i], mTexCoords[i+1]) * hej;
            mTexCoords[i] = newCoords.x;
            mTexCoords[i+1] = newCoords.y;
        }
    }
}
