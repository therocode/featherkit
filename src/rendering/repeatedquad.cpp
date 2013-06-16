#include <framework/rendering/repeatedquad.h>
#include <iostream>

namespace windbreeze
{
    void RepeatedQuad::setTileSize(glm::vec2 size)
    {
        tileSize = size;
    }

    const glm::vec2& RepeatedQuad::getTileSize()
    {
        return tileSize;
    }
    
    void RepeatedQuad::setScrollSpeed(glm::vec2 speed)
    {
        scrollSpeed = speed;
    }

    const glm::vec2& RepeatedQuad::getScrollSpeed() const
    {
        return scrollSpeed;
    }
    
    void RepeatedQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Quad::getRenderData(renderData, time);

        //glm::vec2 texMax = getSize() / tileSize;
        //float texMaxX = texMax.x;
        //float texMaxY = texMax.y;

        renderData.textureId = getTexture();

        /*
        renderData.texCoords =  {0.0f, 0.0f,
                                 0.0f, texMaxY,
                                 texMaxX, texMaxY,
                                 texMaxX, 0.0f};*/

        glm::vec2 hej = getSize() / tileSize;
        for(int i = 0; i < 8; i += 2)
        {
            glm::vec2 newCoords = glm::vec2(renderData.texCoords[i], renderData.texCoords[i+1]) * hej;
            renderData.texCoords[i] = newCoords.x;
            renderData.texCoords[i+1] = newCoords.y;
        }
    }
}
