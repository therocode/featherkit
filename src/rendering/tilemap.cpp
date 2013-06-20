#include <framework/rendering/tilemap.h>
#include <iostream>

namespace windbreeze
{
    TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth, uint32_t tileHeight, float textureTileWidth, float textureTileHeight, uint32_t chunkWidth, uint32_t chunkHeight)
    {
        uint32_t chunkGridWidth = (gridWidth + chunkWidth - 1) / chunkWidth;
        uint32_t chunkGridHeight = (gridHeight + chunkHeight - 1) / chunkHeight;

        chunkGridSize = glm::uvec2(chunkGridWidth, chunkGridHeight);
        chunkSize = glm::uvec2(chunkWidth, chunkHeight);
        gridSize = glm::uvec2(gridWidth, gridHeight);
        textureTileSize = glm::vec2(textureTileWidth, textureTileHeight);
        tileSize = glm::uvec2(tileWidth, tileHeight);

        for(uint32_t y = 0; y < chunkGridHeight; y++)
        {
            for(uint32_t x = 0; x < chunkGridWidth; x++)
            {
                TileChunk newChunk(chunkWidth, chunkHeight, tileWidth, tileHeight);
                glm::vec2 chunkPosition = glm::vec2(position.x + x * chunkWidth * tileWidth, position.y + y * chunkHeight * tileHeight);
                newChunk.setPosition(chunkPosition);
                
                for(uint32_t chunkX = 0; chunkX < chunkWidth; chunkX++)
                {
                    for(uint32_t chunkY = 0; chunkY < chunkHeight; chunkY++)
                    {
                        newChunk.setTileTexCoords(chunkX, chunkY, glm::vec2(0.0f, 0.0f), textureTileSize);
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
    
    void TileMap::addTileDefinition(const std::string& name, const TileDefinition& tileDef)
    {
        tileDefs.emplace(hasher(name), tileDef);
    }

    void TileMap::setTileByName(uint32_t x, uint32_t y, std::string name)
    {
        if(isOutOfBounds(x, y))
            throw std::out_of_range("coordinates out of range");

        setTileById(x, y, hasher(name));
    }

    void TileMap::setTileById(uint32_t x, uint32_t y, TileId id)
    {
        if(isOutOfBounds(x, y))
            throw std::out_of_range("coordinates out of range");

        uint32_t chunkX = x / chunkSize.x;
        uint32_t chunkY = y / chunkSize.y;
        uint32_t chunkIndex = chunkX + chunkY * chunkGridSize.x;

        std::cout << "setting tile, and its coords are " << x << " " << y << "\n";
        std::cout << "setting in chunk, and its coords are " << chunkX << " " << chunkY << " and the index is " << chunkIndex << "\n";

        glm::uvec2 texPos = tileDefs.at(id).tileTexPosition;

        std::cout << "the texture position of the given tile ID is " << texPos.x << " " << texPos.y << "\n";

        chunks[chunkIndex].setTileTexCoords(x - chunkX * chunkSize.x, y - chunkY * chunkSize.y, 
                                            glm::vec2(texPos.x * textureTileSize.x, texPos.y * textureTileSize.y),
                                            glm::vec2(texPos.x * textureTileSize.x + textureTileSize.x, texPos.y * textureTileSize.y + textureTileSize.y));
    }
    
    glm::uvec2 TileMap::getTileByCoordinates(float x, float y)
    {
        if(isOutOfBounds(x, y))
            throw std::out_of_range("coordinates out of range");

        return glm::uvec2(x / tileSize.x, y / tileSize.y);
    }
            
    bool TileMap::isOutOfBounds(uint32_t x, uint32_t y)
    {
        return x > gridSize.x || y > gridSize.y;
    }
}
