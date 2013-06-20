#include <framework/rendering/tilechunk.h>
#include <iostream>

namespace windbreeze
{
    TileChunk::TileChunk(uint32_t width, uint32_t height, uint32_t tileWidth, uint32_t tileHeight)
    {
        float halfTileWidth = ((float) tileWidth) * 0.5f;
        float halfTileHeight = ((float) tileHeight) * 0.5f;

        origin = glm::vec2(0.0f, 0.0f);
        gridSize = glm::uvec2(width, height);

        for(uint32_t y = 0; y < height; y++)
        {
            for(uint32_t x = 0; x < width; x++)
            {
                float xPos = x * tileWidth + tileWidth * 0.5f;
                float yPos = y * tileHeight + tileHeight * 0.5f;

                vertices.push_back(((float)xPos) - halfTileWidth); vertices.push_back(((float)yPos) - halfTileHeight);
                vertices.push_back(((float)xPos) - halfTileWidth); vertices.push_back(((float)yPos) + halfTileHeight);
                vertices.push_back(((float)xPos) + halfTileWidth); vertices.push_back(((float)yPos) + halfTileHeight);
                vertices.push_back(((float)xPos) + halfTileWidth); vertices.push_back(((float)yPos) - halfTileHeight);

                texCoords.push_back(0.0f); texCoords.push_back(0.0f);
                texCoords.push_back(0.0f); texCoords.push_back(1.0f);
                texCoords.push_back(1.0f); texCoords.push_back(1.0f);
                texCoords.push_back(1.0f); texCoords.push_back(0.0f);
            }
        }
    }
    
    void TileChunk::setTexture(const std::string& tex)
    {
        textureId = tex;
    }

    const std::string& TileChunk::getTexture() const
    {
        return textureId;
    }
    
    void TileChunk::setTileTexCoords(uint32_t x, uint32_t y, const glm::vec2 startCoords, const glm::vec2 endCoords)
    {
        uint32_t arrayIndex = getTileIndex(x, y) * 8;
        
        std::cout << "inside the chunk now and setting the internal coords of " << x << " " << y << " to the tex coords " << startCoords.x << " " << startCoords.y << " " << endCoords.x << " " << endCoords.y << "\n";

        texCoords[arrayIndex] = startCoords.x; texCoords[arrayIndex + 1] = startCoords.y;
        texCoords[arrayIndex + 2] = startCoords.x; texCoords[arrayIndex + 3] = endCoords.y;
        texCoords[arrayIndex + 4] = endCoords.x; texCoords[arrayIndex + 5] = endCoords.y;
        texCoords[arrayIndex + 6] = endCoords.x; texCoords[arrayIndex + 7] = startCoords.y;
    }

    void TileChunk::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Drawable2D::getRenderData(renderData, time);

        renderData.textureId = getTexture();

        renderData.texCoords = texCoords;

        std::cout << "filled it with cool texture " << renderData.textureId << "\n";
    }
    
    uint32_t TileChunk::getTileIndex(uint32_t x, uint32_t y)
    {
        return x + y * gridSize.x;
    }
}
