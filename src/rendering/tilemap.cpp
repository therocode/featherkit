#include <framework/rendering/tilemap.h>
#include <iostream>

namespace windbreeze
{
    TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth, uint32_t tileHeight, float textureTileWidth, float textureTileHeight, uint32_t chunkWidth, uint32_t chunkHeight)
    {
        uint32_t chunkGridWidth = (gridWidth + chunkWidth - 1) / chunkWidth;
        uint32_t chunkGridHeight = (gridHeight + chunkHeight - 1) / chunkHeight;

        chunkGridSize = glm::uvec2(chunkGridWidth, chunkGridHeight);

        for(uint32_t x = 0; x < chunkGridWidth; x++)
        {
            for(uint32_t y = 0; y < chunkGridHeight; y++)
            {
                TileChunk newChunk(chunkWidth, chunkHeight, tileWidth, tileHeight);
                glm::vec2 chunkPosition = glm::vec2(position.x + x * chunkWidth * tileWidth, position.y + y * chunkHeight * tileHeight);
                newChunk.setPosition(chunkPosition);
                
                for(uint32_t chunkX = 0; chunkX < chunkWidth; chunkX++)
                {
                    for(uint32_t chunkY = 0; chunkY < chunkHeight; chunkY++)
                    {
                        std::cout << "setting inner tile " << chunkX << " " << chunkY << " to 0.0f, 0.0f " << textureTileWidth << " " << textureTileHeight << "\n";
                        newChunk.setTileTexCoords(chunkX, chunkY, glm::vec2(0.0f, 0.0f), glm::vec2(textureTileWidth, textureTileHeight));
                    }
                }

                chunks.push_back(newChunk);
                std::cout << "pushed a chunk\n";
            }
        }
    }
    
    void TileMap::setPosition(const glm::vec2& pos)
    {
        position = pos;
    }
    
    const glm::vec2& TileMap::getPosition() const
    {
        return position;
    }
    
    const std::vector<TileChunk>& TileMap::getTileChunks() const
    {
        return chunks;
    }
    
    void TileMap::setTexture(const std::string& name)
    {
        textureId = name;

        for(auto& chunk : chunks)
        {
            std::cout << "setting the texture " << name << "\n";
            chunk.setTexture(name);
        }
    }
    
    const std::string& TileMap::getTexture() const
    {
        return textureId;
    }
}
