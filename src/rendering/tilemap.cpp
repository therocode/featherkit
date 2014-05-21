#include <fea/rendering/tilemap.hpp>
#include <fea/assert.hpp>

namespace fea
{
    TileDefinition::TileDefinition(const glm::uvec2& texPos, const std::string& next, uint32_t ticks) : mTileTexPosition(texPos), mNextTile(next), mTicksUntilChange(ticks)
    {
    }
    
    TileMap::AnimatedTile::AnimatedTile(const std::string& next, uint32_t timeLeft) : mNext(next), mTimeLeft(timeLeft)
    {
    }

    TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth, uint32_t tileHeight, float textureTileWidth, float textureTileHeight, uint32_t chunkWidth, uint32_t chunkHeight) : mAnimatedTiles([](const glm::uvec2& first, const glm::uvec2& second)
    { 
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

        FEA_ASSERT(gridWidth > 0 && gridHeight > 0, "The size of the tile grid cannot be zero or below in any dimension! " + std::to_string(gridWidth) + " " + std::to_string(gridHeight) + " provided.");
        FEA_ASSERT(tileWidth > 0 && tileHeight > 0, "The size of the tiles cannot be zero or below in any dimension! " + std::to_string(tileWidth) + " " + std::to_string(tileHeight) + " provided.");
        FEA_ASSERT(textureTileWidth > 0.0f && textureTileHeight > 0.0f, "The size of the tiles in the texture cannot be zero or below in any dimension! " + std::to_string(textureTileWidth) + " " + std::to_string(textureTileHeight) + " provided.");
        FEA_ASSERT(chunkWidth > 0 && chunkHeight > 0, "The size of the tile chunks cannot be zero or below in any dimension! " + std::to_string(chunkWidth) + " " + std::to_string(chunkHeight) + " provided.");

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
        mTileDefs.emplace(name, tileDef);
    }

    void TileMap::setTile(const glm::uvec2& pos, const std::string& name)
    {
        FEA_ASSERT(!isOutOfBounds(pos), "Trying to set tile outside of the bounds of the tilemap! Setting at " + std::to_string(pos.x) + " " + std::to_string(pos.y) + ".");
        uint32_t x = pos.x;
        uint32_t y = pos.y;

        uint32_t chunkX = x / mChunkSize.x;
        uint32_t chunkY = y / mChunkSize.y;
        uint32_t chunkIndex = chunkX + chunkY * mChunkGridSize.x;

        FEA_ASSERT(mTileDefs.find(name) != mTileDefs.end(), "Trying to set tile '" + name + "' which doesn't exist!");

        const TileDefinition& tileDef = mTileDefs.at(name);

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
            AnimatedTile animation(tileDef.mNextTile, tileDef.mTicksUntilChange);
            mAnimatedTiles.emplace(glm::uvec2(x, y), animation);
        }
    }

    void TileMap::unsetTile(const glm::uvec2& pos)
    {
        FEA_ASSERT(!isOutOfBounds(pos), "Trying to unset tile outside of the bounds of the tilemap! Setting at " + std::to_string(pos.x) + " " + std::to_string(pos.y) + ".");

        uint32_t x = pos.x;
        uint32_t y = pos.y;

        uint32_t chunkX = x / mChunkSize.x;
        uint32_t chunkY = y / mChunkSize.y;
        uint32_t chunkIndex = chunkX + chunkY * mChunkGridSize.x;

        mChunks[chunkIndex].unsetTileTexCoords(x - chunkX * mChunkSize.x, y - chunkY * mChunkSize.y);

        if(mAnimatedTiles.find(glm::uvec2(x, y)) != mAnimatedTiles.end())
        {
            mAnimatedTiles.erase(glm::uvec2(x, y));
        }
    }

    void TileMap::fill(const std::string& name)
    {
        FEA_ASSERT(mTileDefs.find(name) != mTileDefs.end(), "Trying to fill tilemap with tile name '" + name + "' which doesn't exist!");

        const TileDefinition& tileDef = mTileDefs.at(name);

        glm::uvec2 texPos = tileDef.mTileTexPosition;

        for(auto& chunk : mChunks)
            chunk.fillTexCoords(glm::vec2((float)texPos.x * mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y),
                                glm::vec2((float)texPos.x * mTextureTileSize.x + mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y + mTextureTileSize.y));

        mAnimatedTiles.clear();

        if(tileDef.mTicksUntilChange > 0)
        {
            AnimatedTile animation(tileDef.mNextTile, tileDef.mTicksUntilChange);

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
    
    glm::uvec2 TileMap::getTileByCoordinates(const glm::vec2& coordinate) const
    {
        FEA_ASSERT(!isOutOfBounds((glm::uvec2)(coordinate / (glm::vec2)mTileSize)), "Cannot access tiles without the bounds of the tilemap! Trying to access at " + std::to_string(coordinate.x) + " " + std::to_string(coordinate.y) + ".");

        return glm::uvec2((uint32_t)coordinate.x / mTileSize.x, (uint32_t)coordinate.y / mTileSize.y);
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
        std::vector<std::string> names;

        for(auto animated = mAnimatedTiles.begin(); animated != mAnimatedTiles.end();)
        {
            if(animated->second.mTimeLeft == 0)
            {
                uint32_t x = animated->first.x;
                uint32_t y = animated->first.y;
                const std::string& name = animated->second.mNext;
                animated = mAnimatedTiles.erase(animated);
                
                toSet.push_back(glm::uvec2(x, y));
                names.push_back(name);
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
            setTile(toSet[i], names[i]);
        }
    }

    void TileMap::setOpacity(float opacity)
    {
        for(auto& chunk : mChunks)
            chunk.setOpacity(opacity);
    }

    float TileMap::getOpacity() const
    {
        return mChunks.begin()->getOpacity();
    }
}
