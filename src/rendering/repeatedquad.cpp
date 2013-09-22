#include <featherkit/rendering/repeatedquad.h>
#include <iostream>

namespace fea
{
    RepeatedQuad::RepeatedQuad() : AnimatedQuad() 
    {
        tileSize = getSize();
        updateConstraints();
    }

    RepeatedQuad::RepeatedQuad(float w, float h) : AnimatedQuad(w, h) 
    {
        tileSize = getSize();
        updateConstraints();
    }

    RepeatedQuad::RepeatedQuad(const glm::vec2& size) : AnimatedQuad(size)
    {
        tileSize = getSize();
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
        tileSize = glm::vec2(w, h);
        updateConstraints();
    }

    void RepeatedQuad::setTileSize(const glm::vec2& size)
    {
        tileSize = size;
        updateConstraints();
    }

    const glm::vec2& RepeatedQuad::getTileSize()
    {
        return tileSize;
    }
    
    void RepeatedQuad::setScrollSpeed(float xSpeed, float ySpeed) //FIX
    {
        scrollSpeed = glm::vec2(xSpeed, ySpeed);
    }
    
    void RepeatedQuad::setScrollSpeed(const glm::vec2& speed)
    {
        scrollSpeed = speed;
    }

    const glm::vec2& RepeatedQuad::getScrollSpeed() const
    {
        return scrollSpeed;
    }
    
    void RepeatedQuad::updateConstraints()
    {
        glm::vec2 hej = getSize() / tileSize;
        std::cout << "ojojojoj the sizes were " << getSize().x << " " << getSize().y << " tile: " << tileSize.x << " " << tileSize.y << " hej " << hej.x << " "<< hej.y << "\n";
        std::cout << "and constraints are " << constraints[0] << " " << constraints[1] << " " << constraints[2] << " " << constraints[3] << "\n";

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * hFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * vFlip;

        texCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        for(uint32_t i = 0; i < 12; i += 2)
        {
            glm::vec2 newCoords = glm::vec2(texCoords[i], texCoords[i+1]) * hej;
            texCoords[i] = newCoords.x;
            texCoords[i+1] = newCoords.y;
        }
    }
    /*
    void RepeatedQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        AnimatedQuad::getRenderData(renderData, time);

        //glm::vec2 texMax = getSize() / tileSize;
        //float texMaxX = texMax.x;
        //float texMaxY = texMax.y;

        \*
        renderData.texCoords =  {0.0f, 0.0f,
                                 0.0f, texMaxY,
                                 texMaxX, texMaxY,
                                 texMaxX, 0.0f};*\

        renderData.textureScroll = scrollSpeed * (float)time;

        glm::vec2 hej = getSize() / tileSize;
        for(uint32_t i = 0; i < 12; i += 2)
        {
            glm::vec2 newCoords = glm::vec2(renderData.texCoords[i], renderData.texCoords[i+1]) * hej;
            renderData.texCoords[i] = newCoords.x;
            renderData.texCoords[i+1] = newCoords.y;
        }
        //currentScroll = currentScroll + scrollSpeed; must be done later
    }*/
}
