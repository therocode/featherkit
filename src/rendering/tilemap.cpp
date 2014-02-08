#include <featherkit/rendering/tilemap.h>
#include <sstream>

namespace fea
{
    TileDefinition::TileDefinition(glm::uvec2 texPos, TileId nextId, uint32_t ticks) : mTileTexPosition(texPos), mNextTileId(nextId), mTicksUntilChange(ticks)
    {
    }

    TileDefinition::TileDefinition(uint32_t texX, uint32_t texY, TileId nextId, uint32_t ticks) : mTileTexPosition(glm::uvec2(texX, texY)), mNextTileId(nextId), mTicksUntilChange(ticks)
    {
    }
    
    TileMapException::TileMapException(const std::string& message) : std::runtime_error(message)
    {
    }

    TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth, uint32_t tileHeight, float textureTileWidth, float textureTileHeight, uint32_t chunkWidth, uint32_t chunkHeight) : mAnimatedTiles([](const glm::uvec2& first, const glm::uvec2& second){ 
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

        mChunkGridSize = glm::uvec2(chunkGridWidth, chunkGridHeight);
        mChunkSize = glm::uvec2(chunkWidth, chunkHeight);
        mGridSize = glm::uvec2(gridWidth, gridHeight);
        mTextureTileSize = glm::vec2(textureTileWidth, textureTileHeight);
        mTileSize = glm::uvec2(tileWidth, tileHeight);

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
                glm::vec2 chunkPosition = glm::vec2(mPosition.x +(float) (x * chunkWidth * tileWidth),mPosition.y + (float)(y * chunkHeight * tileHeight));
                newChunk.setPosition(chunkPosition);
                
                for(uint32_t chunkX = 0; chunkX < newChunkWidth; chunkX++)
                {
                    for(uint32_t chunkY = 0; chunkY < newChunkHeight; chunkY++)
                    {
                        //newChunk.setTileTexCoords(chunkX, chunkY, glm::vec2(0.0f, 0.0f), mTextureTileSize);
                    }
                }

                newChunk.setOrigin(glm::vec2(0.0f, 0.0f));
                mChunks.push_back(newChunk);
            }
        }
    }

    void TileMap::setPosition(float xPos, float yPos)
    {
        mPosition = glm::vec2(xPos, yPos);

        for(uint32_t y = 0; y < mChunkGridSize.y; y++)
        {
            for(uint32_t x = 0; x < mChunkGridSize.x; x++)
            {
                glm::vec2 chunkPosition = glm::vec2(mPosition.x + (float)(x * mChunkSize.x * mTileSize.x), mPosition.y + (float)(y * mChunkSize.y * mTileSize.y));

                mChunks[x + y * mChunkGridSize.x].setPosition(chunkPosition);
            }
        }
    }

    void TileMap::setPosition(const glm::vec2& pos)
    {
        mPosition = pos;

        for(uint32_t y = 0; y < mChunkGridSize.y; y++)
        {
            for(uint32_t x = 0; x < mChunkGridSize.x; x++)
            {
                glm::vec2 chunkPosition = glm::vec2(mPosition.x + (float)(x * mChunkSize.x * mTileSize.x), mPosition.y + (float)(y * mChunkSize.y * mTileSize.y));

                mChunks[x + y * mChunkGridSize.x].setPosition(chunkPosition);
            }
        }
    }
    
    const glm::vec2& TileMap::getPosition() const
    {
        return mPosition;
    }
    
    const std::vector<TileChunk>& TileMap::getTileChunks() const
    {
        return mChunks;
    }
    
    void TileMap::setTexture(const Texture& tex)
    {
        mTexture = &tex;

        for(auto& chunk : mChunks)
        {
            chunk.setTexture(tex);
        }
    }
    
    const Texture& TileMap::getTexture() const
    {
        return *mTexture;
    }
    
    void TileMap::addTileDefinition(const std::string& name, const TileDefinition& tileDef)
    {
        mTileDefs.emplace(mHasher(name), tileDef);
    }

    void TileMap::setTile(uint32_t x, uint32_t y, const std::string& name)
    {
        if(isOutOfBounds(x, y))
        {
            std::stringstream ss;
            ss << "Error! Coordinates " << x << " and " << y << " out of range (" << mGridSize.x << "," << mGridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        setTile(x, y, mHasher(name));
    }

    void TileMap::setTile(const glm::uvec2& pos, const std::string& name)
    {
        if(isOutOfBounds(pos.x, pos.y))
        {
            std::stringstream ss;
            ss << "Error! Coordinates " << pos.x << " and " << pos.y << " out of range (" << mGridSize.x << "," << mGridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        setTile(pos.x, pos.y, mHasher(name));
    }

    void TileMap::setTile(uint32_t x, uint32_t y, TileId id)
    {
        if(isOutOfBounds(x, y))
        {
            std::stringstream ss;
            ss << "Error! Coordinates " << x << " and " << y << " out of range (" << mGridSize.x << "," << mGridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        uint32_t chunkX = x / mChunkSize.x;
        uint32_t chunkY = y / mChunkSize.y;
        uint32_t chunkIndex = chunkX + chunkY * mChunkGridSize.x;

        auto tileIter = mTileDefs.find(id);
        if(tileIter == mTileDefs.end())
        {
            throw(TileMapException("Error! Tile does not exist!\n"));
        }

        TileDefinition tileDef = tileIter->second;

        glm::uvec2 texPos = tileDef.mTileTexPosition;

        mChunks[chunkIndex].setTileTexCoords(x - chunkX * mChunkSize.x, y - chunkY * mChunkSize.y, 
                                            glm::vec2((float)texPos.x * mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y),
                                            glm::vec2((float)texPos.x * mTextureTileSize.x + mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y + mTextureTileSize.y));

        if(mAnimatedTiles.find(glm::uvec2(x, y)) != mAnimatedTiles.end())
        {
            mAnimatedTiles.erase(glm::uvec2(x, y));
        }

        if(tileDef.mTicksUntilChange > 0)
        {
            AnimatedTile animation;
            animation.mNext = tileDef.mNextTileId;
            animation.mTimeLeft = tileDef.mTicksUntilChange;
            mAnimatedTiles.emplace(glm::uvec2(x, y), animation);
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
            ss << "Error! Coordinates " << x << " and " << y << " out of range (" << mGridSize.x << "," << mGridSize.y << ")\n";
            throw TileMapException(ss.str());
        }

        uint32_t chunkX = x / mChunkSize.x;
        uint32_t chunkY = y / mChunkSize.y;
        uint32_t chunkIndex = chunkX + chunkY * mChunkGridSize.x;

        mChunks[chunkIndex].unsetTileTexCoords(x - chunkX * mChunkSize.x, y - chunkY * mChunkSize.y);

        if(mAnimatedTiles.find(glm::uvec2(x, y)) != mAnimatedTiles.end())
        {
            mAnimatedTiles.erase(glm::uvec2(x, y));
        }
    }

    void TileMap::unsetTile(const glm::uvec2& pos)
    {
        unsetTile(pos.x, pos.y);
    }

    void TileMap::fill(const std::string& name)
    {
        fill(mHasher(name));
    }

    void TileMap::fill(TileId id)
    {
        auto tileIter = mTileDefs.find(id);
        if(tileIter == mTileDefs.end())
        {
            throw(TileMapException("Error! Tile does not exist!\n"));
        }

        TileDefinition tileDef = tileIter->second;

        glm::uvec2 texPos = tileDef.mTileTexPosition;

        for(auto& chunk : mChunks)
            chunk.fillTexCoords(glm::vec2((float)texPos.x * mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y),
                                glm::vec2((float)texPos.x * mTextureTileSize.x + mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y + mTextureTileSize.y));

        mAnimatedTiles.clear();

        if(tileDef.mTicksUntilChange > 0)
        {
            AnimatedTile animation;
            animation.mNext = tileDef.mNextTileId;
            animation.mTimeLeft = tileDef.mTicksUntilChange;

            for(uint32_t x = 0; x < mGridSize.x; x++)
            {
                for(uint32_t y = 0; y < mGridSize.y; y++)
                {
                    mAnimatedTiles.emplace(glm::uvec2(x, y), animation);
                }
            }
        }
    }
    
    void TileMap::clear()
    {
        for(auto& chunk : mChunks)
            chunk.clear();

        mAnimatedTiles.clear();
    }
    
    TileId TileMap::getTileId(const std::string& name) const
    {
        return mHasher(name);
    }
    
    glm::uvec2 TileMap::getTileByCoordinates(float x, float y) const
    {
        if(isOutOfBounds(((uint32_t)x) / mTileSize.x, ((uint32_t)y) / mTileSize.y))
            throw TileMapException("coordinates out of range");

        return glm::uvec2((uint32_t)x / mTileSize.x, (uint32_t)y / mTileSize.y);
    }
    
    glm::uvec2 TileMap::getTileByCoordinates(const glm::vec2& coordinate) const
    {
        if(isOutOfBounds(((uint32_t)coordinate.x) / mTileSize.x, ((uint32_t)coordinate.y) / mTileSize.y))
            throw TileMapException("coordinates out of range");

        return glm::uvec2((uint32_t)coordinate.x / mTileSize.x, (uint32_t)coordinate.y / mTileSize.y);
    }
            
    bool TileMap::isOutOfBounds(uint32_t x, uint32_t y) const
    {
        return (x >= mGridSize.x) || (y >= mGridSize.y);
    }
            
    bool TileMap::isOutOfBounds(const glm::uvec2& pos) const
    {
        return (pos.x >= mGridSize.x) || (pos.y >= mGridSize.y);
    }
    
    glm::uvec2 TileMap::getTileSize() const
    {
        return mTileSize;
    }

    glm::uvec2 TileMap::getGridSize() const
    {
        return mGridSize;
    }

    glm::uvec2 TileMap::getTileMapSize() const
    {
        return mTileSize * mGridSize;
    }

    void TileMap::tick()
    {
        std::vector<glm::uvec2> toSet;
        std::vector<TileId> ids;

        for(auto animated = mAnimatedTiles.begin(); animated != mAnimatedTiles.end();)
        {
            if(animated->second.mTimeLeft == 0)
            {
                uint32_t x = animated->first.x;
                uint32_t y = animated->first.y;
                TileId id = animated->second.mNext;
                animated = mAnimatedTiles.erase(animated);
                
                toSet.push_back(glm::uvec2(x, y));
                ids.push_back(id);
                continue;
            }
            else
            {
                animated->second.mTimeLeft--;
                animated++;
            }
        }
        for(uint32_t i = 0; i < toSet.size(); i++)
        {
            setTile(toSet[i].x, toSet[i].y, ids[i]);
        }
    }
}
