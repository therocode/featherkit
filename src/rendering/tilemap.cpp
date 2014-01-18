#include <featherkit/rendering/tilemap.h>
#include <sstream>

namespace fea
{
    TileDefinition::TileDefinition(glm::uvec2 texPos, TileId nextId, uint32_t ticks) : tileTexPosition(texPos), nextTileId(nextId), ticksUntilChange(ticks)
    {
    }

    TileDefinition::TileDefinition(uint32_t texX, uint32_t texY, TileId nextId, uint32_t ticks) : tileTexPosition(glm::uvec2(texX, texY)), nextTileId(nextId), ticksUntilChange(ticks)
    {
    }
    
    TileMapException::TileMapException(const std::string& message) : std::runtime_error(message)
    {
    }

    TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth, uint32_t tileHeight, float textureTileWidth, float textureTileHeight, uint32_t chunkWidth, uint32_t chunkHeight) : animatedTiles([](const glm::uvec2& first, const glm::uvec2& second){ 
                if(first.x < second.x) 
                    return true;
                else if(first.x > second.x)
                    return false;
                else
                {
                if(first.y < second.y) 
                    return true;
                else
                    return false;
                }
           })
    {
        uint32_t chunkGridWidth = (gridWidth + chunkWidth - 1) / chunkWidth;
        uint32_t chunkGridHeight = (gridHeight + chunkHeight - 1) / chunkHeight;

        chunkGridSize = glm::uvec2(chunkGridWidth, chunkGridHeight);
        chunkSize = glm::uvec2(chunkWidth, chunkHeight);
        gridSize = glm::uvec2(gridWidth, gridHeight);
        textureTileSize = glm::vec2(textureTileWidth, textureTileHeight);
        tileSize = glm::uvec2(tileWidth, tileHeight);

        bool uneven = gridWidth % chunkWidth != 0;
        glm::uvec2 edgeSize(gridWidth % chunkWidth, gridHeight % chunkHeight);

        uint32_t newChunkHeight = chunkHeight;

        for(uint32_t y = 0; y < chunkGridHeight; y++)
        {
            if(y == chunkGridHeight - 1 && uneven)
                newChunkHeight = edgeSize.y;

            uint32_t newChunkWidth = chunkWidth;
            for(uint32_t x = 0; x < chunkGridWidth; x++)
            {
                if(x == chunkGridWidth - 1 && uneven)
                    newChunkWidth = edgeSize.x;
    
                TileChunk newChunk(newChunkWidth, newChunkHeight, tileWidth, tileHeight);
                glm::vec2 chunkPosition = glm::vec2(position.x +(float) (x * chunkWidth * tileWidth),position.y + (float)(y * chunkHeight * tileHeight));
                newChunk.setPosition(chunkPosition);
                
                for(uint32_t chunkX = 0; chunkX < newChunkWidth; chunkX++)
                {
                    for(uint32_t chunkY = 0; chunkY < newChunkHeight; chunkY++)
                    {
                        //newChunk.setTileTexCoords(chunkX, chunkY, glm::vec2(0.0f, 0.0f), textureTileSize);
                    }
                }

                newChunk.setOrigin(glm::vec2(0.0f, 0.0f));
                chunks.push_back(newChunk);
            }
        }
    }

    void TileMap::setPosition(float xPos, float yPos)
    {
        position = glm::vec2(xPos, yPos);

        for(uint32_t y = 0; y < chunkGridSize.y; y++)
        {
            for(uint32_t x = 0; x < chunkGridSize.x; x++)
            {
                glm::vec2 chunkPosition = glm::vec2(position.x + (float)(x * chunkSize.x * tileSize.x), position.y + (float)(y * chunkSize.y * tileSize.y));

                chunks[x + y * chunkGridSize.x].setPosition(chunkPosition);
            }
        }
    }

    void TileMap::setPosition(const glm::vec2& pos)
    {
        position = pos;

        for(uint32_t y = 0; y < chunkGridSize.y; y++)
        {
            for(uint32_t x = 0; x < chunkGridSize.x; x++)
            {
                glm::vec2 chunkPosition = glm::vec2(position.x + (float)(x * chunkSize.x * tileSize.x), position.y + (float)(y * chunkSize.y * tileSize.y));

                chunks[x + y * chunkGridSize.x].setPosition(chunkPosition);
            }
        }
    }
    
    const glm::vec2& TileMap::getPosition() const
    {
        return position;
    }
    
    const std::vector<TileChunk>& TileMap::getTileChunks() const
    {
        return chunks;
    }
    
    void TileMap::setTexture(const Texture& tex)
    {
        texture = &tex;

        for(auto& chunk : chunks)
        {
            chunk.setTexture(tex);
        }
    }
    
    const Texture& TileMap::getTexture() const
    {
        return *texture;
    }
    
    void TileMap::addTileDefinition(const std::string& name, const TileDefinition& tileDef)
    {
        tileDefs.emplace(hasher(name), tileDef);
    }

    void TileMap::setTile(uint32_t x, uint32_t y, const std::string& name)
    {
        if(isOutOfBounds(x, y))
        {
            std::stringstream ss;
            ss << "Error! Coordinates " << x << " and " << y << " out of range (" << gridSize.x << "," << gridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        setTile(x, y, hasher(name));
    }

    void TileMap::setTile(const glm::uvec2& pos, const std::string& name)
    {
        if(isOutOfBounds(pos.x, pos.y))
        {
            std::stringstream ss;
            ss << "Error! Coordinates " << pos.x << " and " << pos.y << " out of range (" << gridSize.x << "," << gridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        setTile(pos.x, pos.y, hasher(name));
    }

    void TileMap::setTile(uint32_t x, uint32_t y, TileId id)
    {
        if(isOutOfBounds(x, y))
        {
            std::stringstream ss;
            ss << "Error! Coordinates " << x << " and " << y << " out of range (" << gridSize.x << "," << gridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        uint32_t chunkX = x / chunkSize.x;
        uint32_t chunkY = y / chunkSize.y;
        uint32_t chunkIndex = chunkX + chunkY * chunkGridSize.x;

        auto tileIter = tileDefs.find(id);
        if(tileIter == tileDefs.end())
        {
            throw(TileMapException("Error! Tile does not exist!\n"));
        }

        TileDefinition tileDef = tileIter->second;

        glm::uvec2 texPos = tileDef.tileTexPosition;

        chunks[chunkIndex].setTileTexCoords(x - chunkX * chunkSize.x, y - chunkY * chunkSize.y, 
                                            glm::vec2((float)texPos.x * textureTileSize.x, (float)texPos.y * textureTileSize.y),
                                            glm::vec2((float)texPos.x * textureTileSize.x + textureTileSize.x, (float)texPos.y * textureTileSize.y + textureTileSize.y));

        if(animatedTiles.find(glm::uvec2(x, y)) != animatedTiles.end())
        {
            animatedTiles.erase(glm::uvec2(x, y));
        }

        if(tileDef.ticksUntilChange > 0)
        {
            AnimatedTile animation;
            animation.next = tileDef.nextTileId;
            animation.timeLeft = tileDef.ticksUntilChange;
            animatedTiles.emplace(glm::uvec2(x, y), animation);
        }
    }

    void TileMap::setTile(const glm::uvec2& pos, TileId id)
    {
        setTile(pos.x, pos.y, id);
    }

    void TileMap::unsetTile(uint32_t x, uint32_t y)
    {
        if(isOutOfBounds(x, y))
        {
            std::stringstream ss;
            ss << "Error! Coordinates " << x << " and " << y << " out of range (" << gridSize.x << "," << gridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        uint32_t chunkX = x / chunkSize.x;
        uint32_t chunkY = y / chunkSize.y;
        uint32_t chunkIndex = chunkX + chunkY * chunkGridSize.x;

        chunks[chunkIndex].unsetTileTexCoords(x - chunkX * chunkSize.x, y - chunkY * chunkSize.y);

        if(animatedTiles.find(glm::uvec2(x, y)) != animatedTiles.end())
        {
            animatedTiles.erase(glm::uvec2(x, y));
        }
    }

    void TileMap::unsetTile(const glm::uvec2& pos)
    {
        unsetTile(pos.x, pos.y);
    }

    void TileMap::fill(const std::string& name)
    {
        fill(hasher(name));
    }

    void TileMap::fill(TileId id)
    {
        auto tileIter = tileDefs.find(id);
        if(tileIter == tileDefs.end())
        {
            throw(TileMapException("Error! Tile does not exist!\n"));
        }

        TileDefinition tileDef = tileIter->second;

        glm::uvec2 texPos = tileDef.tileTexPosition;

        for(auto& chunk : chunks)
            chunk.fillTexCoords(glm::vec2((float)texPos.x * textureTileSize.x, (float)texPos.y * textureTileSize.y),
                                glm::vec2((float)texPos.x * textureTileSize.x + textureTileSize.x, (float)texPos.y * textureTileSize.y + textureTileSize.y));

        animatedTiles.clear();

        if(tileDef.ticksUntilChange > 0)
        {
            AnimatedTile animation;
            animation.next = tileDef.nextTileId;
            animation.timeLeft = tileDef.ticksUntilChange;

            for(uint32_t x = 0; x < gridSize.x; x++)
            {
                for(uint32_t y = 0; y < gridSize.y; y++)
                {
                    animatedTiles.emplace(glm::uvec2(x, y), animation);
                }
            }
        }
    }
    
    void TileMap::clear()
    {
        for(auto& chunk : chunks)
            chunk.clear();

        animatedTiles.clear();
    }
    
    TileId TileMap::getTileId(const std::string& name) const
    {
        return hasher(name);
    }
    
    glm::uvec2 TileMap::getTileByCoordinates(float x, float y) const
    {
        if(isOutOfBounds(((uint32_t)x) / tileSize.x, ((uint32_t)y) / tileSize.y))
            throw TileMapException("coordinates out of range");

        return glm::uvec2((uint32_t)x / tileSize.x, (uint32_t)y / tileSize.y);
    }
    
    glm::uvec2 TileMap::getTileByCoordinates(const glm::vec2& coordinate) const
    {
        if(isOutOfBounds(((uint32_t)coordinate.x) / tileSize.x, ((uint32_t)coordinate.y) / tileSize.y))
            throw TileMapException("coordinates out of range");

        return glm::uvec2((uint32_t)coordinate.x / tileSize.x, (uint32_t)coordinate.y / tileSize.y);
    }
            
    bool TileMap::isOutOfBounds(uint32_t x, uint32_t y) const
    {
        return (x >= gridSize.x) || (y >= gridSize.y);
    }
            
    bool TileMap::isOutOfBounds(const glm::uvec2& pos) const
    {
        return (pos.x >= gridSize.x) || (pos.y >= gridSize.y);
    }
    
    glm::uvec2 TileMap::getTileSize() const
    {
        return tileSize;
    }

    glm::uvec2 TileMap::getGridSize() const
    {
        return gridSize;
    }

    glm::uvec2 TileMap::getTileMapSize() const
    {
        return tileSize * gridSize;
    }

    void TileMap::tick()
    {
        std::vector<glm::uvec2> toSet;
        std::vector<TileId> ids;

        for(auto animated = animatedTiles.begin(); animated != animatedTiles.end();)
        {
            if(animated->second.timeLeft == 0)
            {
                uint32_t x = animated->first.x;
                uint32_t y = animated->first.y;
                TileId id = animated->second.next;
                animated = animatedTiles.erase(animated);
                
                toSet.push_back(glm::uvec2(x, y));
                ids.push_back(id);
                continue;
            }
            else
            {
                animated->second.timeLeft--;
                animated++;
            }
        }
        for(uint32_t i = 0; i < toSet.size(); i++)
        {
            setTile(toSet[i].x, toSet[i].y, ids[i]);
        }
    }
}
