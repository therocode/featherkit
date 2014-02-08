#include <featherkit/rendering/repeatedquad.h>

namespace fea
{
    RepeatedQuad::RepeatedQuad() : AnimatedQuad() 
    {
        mTileSize = getSize();
        updateConstraints();
    }

    RepeatedQuad::RepeatedQuad(float w, float h) : AnimatedQuad(w, h) 
    {
        mTileSize = getSize();
        updateConstraints();
    }

    RepeatedQuad::RepeatedQuad(const glm::vec2& size) : AnimatedQuad(size)
    {
        mTileSize = getSize();
        updateConstraints();
    }

    void RepeatedQuad::setSize(float w, float h)
    {
        Quad::setSize(w, h);
        updateConstraints();
    }

    void RepeatedQuad::setSize(glm::vec2 size)
    {
        Quad::setSize(size);
        updateConstraints();
    }

    void RepeatedQuad::setTileSize(float w, float h)
    {
        mTileSize = glm::vec2(w, h);
        updateConstraints();
    }

    void RepeatedQuad::setTileSize(const glm::vec2& size)
    {
        mTileSize = size;
        updateConstraints();
    }

    const glm::vec2& RepeatedQuad::getTileSize()
    {
        return mTileSize;
    }
    
    void RepeatedQuad::setScrollSpeed(float xSpeed, float ySpeed) //FIX
    {
        mScrollSpeed = glm::vec2(xSpeed, ySpeed);
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

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * hFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * vFlip;

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        for(uint32_t i = 0; i < 12; i += 2)
        {
            glm::vec2 newCoords = glm::vec2(texCoords[i], texCoords[i+1]) * hej;
            mTexCoords[i] = newCoords.x;
            mTexCoords[i+1] = newCoords.y;
        }
    }
}
