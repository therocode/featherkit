#include <fea/rendering/tilemap.hpp>
#include <fea/assert.hpp>

namespace fea
{
    const int32_t tileMapChunkSize = 32;

    TileDefinition::TileDefinition(const glm::ivec2& texPos, TileId next, int32_t ticks):
        tileTexPosition(texPos),
        nextTile(next),
        ticksUntilChange(ticks)
    {
    }

    TileMap::TileChunk::TileChunk():
        tileCount(0),
        tilesSet(tileMapChunkSize*tileMapChunkSize, false)
    {
        tiles.resize(tileMapChunkSize*tileMapChunkSize);
    }

    void TileMap::TileChunk::setTile(const glm::ivec2& position, TileId id)
    {
        size_t index = position.x + position.y * tileMapChunkSize;
        tiles[index].id = id;
        tiles[index].color = fea::Color::White;

        if(!tilesSet[index])
        {
            tilesSet[index] = true;
            tileCount++;
        };
    }

    void TileMap::TileChunk::setTileColor(const glm::ivec2& position, const fea::Color& color)
    {
        size_t index = position.x + position.y * tileMapChunkSize;

        //ensure tile is set
        tiles[index].color = color;
    }

    const TileMap::Tile& TileMap::TileChunk::getTile(const glm::ivec2& position) const
    {
        size_t index = position.x + position.y * tileMapChunkSize;

        //ensure tile is set
        return tiles[index];
    }

    TileMap::Tile& TileMap::TileChunk::getTile(const glm::ivec2& position)
    {
        size_t index = position.x + position.y * tileMapChunkSize;

        //ensure tile is set
        return tiles[index];
    }

    void TileMap::TileChunk::unsetTile(const glm::ivec2& position)
    {
        size_t index = position.x + position.y * tileMapChunkSize;

        if(tilesSet[index])
        {
            tilesSet[index] = false;
            tileCount--;
        };
    }

    TileMap::TileMap(const glm::ivec2& tileSize, const glm::ivec2& tileTextureSize):
        mTileSize(tileSize),
        mTileTextureSize(tileTextureSize)
    {
    }

    void TileMap::setTexture(const Texture& texture)
    {
        mTexture = &texture;
    }

    const Texture& TileMap::getTexture() const
    {
        return *mTexture;
    }

    void TileMap::addTileDefinition(TileId id, const TileDefinition& tileDef)
    {
        mTileDefinitions.emplace(id, tileDef);
    }

    void TileMap::setTile(const glm::ivec2& pos, TileId id)
    {
        const glm::ivec2 chunkCoord = tileToChunk(pos);
        const glm::ivec2 tileInChunkCoord = tileToTileInChunk(pos);

        auto& chunk = mChunks[chunkCoord];

        chunk.setTile(tileInChunkCoord, id);

        const auto& definition = mTileDefinitions.at(id);
        if(definition.nextTile != -1)
        {
            auto& tile = mAnimatedTiles[pos];
            tile = &chunk.getTile(tileInChunkCoord);
            tile->ticksUntilChange = definition.ticksUntilChange;
        }
        else
        {
            mAnimatedTiles.erase(pos);
        }
    }

    void TileMap::unsetTile(const glm::ivec2& pos)
    {
        const glm::ivec2 chunkCoord = tileToChunk(pos);
        const glm::ivec2 tileInChunkCoord = tileToTileInChunk(pos);

        auto& chunk = mChunks[chunkCoord];

        chunk.unsetTile(tileInChunkCoord);

        if(chunk.tileCount == 0)
        {
            mChunks.erase(chunkCoord);
        }

        auto animatedIterator = mAnimatedTiles.find(pos);
        mAnimatedTiles.erase(animatedIterator);
    }

    void TileMap::fillRegion(glm::ivec2 startCorner, glm::ivec2 endCorner, TileId id)
    {
        if(startCorner.x > endCorner.x)
            std::swap(startCorner.x, endCorner.x);
        if(startCorner.y > endCorner.y)
            std::swap(startCorner.y, endCorner.y);
            
        for(int32_t x = startCorner.x; x <= endCorner.x; ++x)
        {
            for(int32_t y = startCorner.y; y <= endCorner.y; ++y)
            {
                setTile({x, y}, id);
            }
        }
    }

    void TileMap::clear()
    {
        mChunks.clear();
        mAnimatedTiles.clear();
    }

    void TileMap::setTileColor(const glm::ivec2& pos, const fea::Color& color)
    {
        //assert that tile exists
        const glm::ivec2 chunkCoord = tileToChunk(pos);
        const glm::ivec2 tileInChunkCoord = tileToTileInChunk(pos);

        auto& chunk = mChunks[chunkCoord];

        chunk.setTileColor(tileInChunkCoord, color);
    }

    const TileMap::Tile& TileMap::getTile(const glm::ivec2& pos) const
    {
        //assert that tile exists
        const glm::ivec2 chunkCoord = tileToChunk(pos);
        const glm::ivec2 tileInChunkCoord = tileToTileInChunk(pos);

        auto& chunk = mChunks.at(chunkCoord);

        return chunk.getTile(tileInChunkCoord);
    }
    
    glm::ivec2 TileMap::worldToTileCoordinates(const glm::vec2& coordinate) const
    {
        float sin = glm::sin(-getRotation());
        float cos = glm::cos(-getRotation());

        glm::mat2x2 rot = glm::mat2x2(cos, sin, -sin, cos);
        glm::vec2 scale = getScale();

        glm::vec2 transformedCoordinate = ((glm::inverse(rot) * (coordinate - mPosition)) + getOrigin()) / scale;

        return static_cast<glm::ivec2>(transformedCoordinate) / mTileSize;
    }

    const glm::ivec2& TileMap::getTileSize() const
    {
        return mTileSize;
    }

    const glm::ivec2& TileMap::getTileTextureSize() const
    {
        return mTileTextureSize;
    }

    void TileMap::tick()
    {
        std::unordered_map<glm::ivec2, TileId> tilesToSet;

        for(auto tileIter : mAnimatedTiles)
        {
            if(--tileIter.second->ticksUntilChange == 0)
            {
                TileId nextTile = mTileDefinitions.at(tileIter.second->id).nextTile;
                tilesToSet.emplace(tileIter.first, nextTile);
            }
        }

        for(auto tileIter : tilesToSet)
        {
            setTile(tileIter.first, tileIter.second);
        }
    }
            
    std::vector<RenderEntity> TileMap::getRenderInfo() const
    {
        std::vector<RenderEntity> renderInfo;

        for(auto chunk : mChunks)
        {
            renderInfo.push_back(renderInfoFromChunk(chunk.first, chunk.second));
        }

        return renderInfo;
    }

    glm::ivec2 TileMap::tileToChunk(const glm::ivec2& pos) const
    {
        return glm::ivec2(pos.x >= 0 ? pos.x / tileMapChunkSize : (pos.x+1) / tileMapChunkSize - 1, pos.y >= 0 ? pos.y / tileMapChunkSize : (pos.y+1) / tileMapChunkSize - 1); //takes <0 into account
    }
    
    glm::ivec2 TileMap::tileToTileInChunk(const glm::ivec2& pos) const
    {
        return glm::ivec2(pos.x >= 0 ? pos.x % tileMapChunkSize : pos.x % tileMapChunkSize + tileMapChunkSize, pos.y >= 0 ? pos.y % tileMapChunkSize : pos.y % tileMapChunkSize + tileMapChunkSize); //takes <0 into account
    }

    RenderEntity TileMap::renderInfoFromChunk(const glm::ivec2& chunkPos, const TileChunk& chunk) const
    {
        glm::vec2 worldPos = static_cast<glm::vec2>(chunkPos * tileMapChunkSize * mTileSize);

        size_t index = 0;

        std::vector<float> vertices;
        std::vector<float> texCoords;
        std::vector<float> vertexColors;
        glm::vec2 tilePos;

        for(int32_t y = 0; y < tileMapChunkSize; ++y)
        {
            tilePos.y = worldPos.y + y * mTileSize.y;
            for(int32_t x = 0; x < tileMapChunkSize; ++x)
            {
                if(chunk.tilesSet[index])
                {
                    TileId tileId = chunk.tiles[index].id;
                    const fea::Color& tileColor = chunk.tiles[index].color;

                    FEA_ASSERT(mTileDefinitions.count(tileId) != 0, "Set tile does not exist. This is a bug in feather kit");
                    tilePos.x = worldPos.x + x * mTileSize.x;

                    vertices.push_back(tilePos.x              ); vertices.push_back(tilePos.y              );
                    vertices.push_back(tilePos.x              ); vertices.push_back(tilePos.y + mTileSize.y);
                    vertices.push_back(tilePos.x + mTileSize.x); vertices.push_back(tilePos.y              );
                    vertices.push_back(tilePos.x + mTileSize.x); vertices.push_back(tilePos.y              );
                    vertices.push_back(tilePos.x              ); vertices.push_back(tilePos.y + mTileSize.y);
                    vertices.push_back(tilePos.x + mTileSize.x); vertices.push_back(tilePos.y + mTileSize.y);

                    glm::vec2 startTexCoords;
                    glm::vec2 endTexCoords = {1.0f, 1.0f};


                    if(mTexture)
                    {
                        startTexCoords = static_cast<glm::vec2>(mTileDefinitions.at(tileId).tileTexPosition * mTileTextureSize) / static_cast<glm::vec2>(mTexture->getSize());
                        endTexCoords = startTexCoords + static_cast<glm::vec2>(mTileTextureSize) / static_cast<glm::vec2>(mTexture->getSize());
                    }

                    texCoords.push_back(startTexCoords.x); texCoords.push_back(startTexCoords.y);
                    texCoords.push_back(startTexCoords.x); texCoords.push_back(endTexCoords.y);
                    texCoords.push_back(endTexCoords.x); texCoords.push_back(startTexCoords.y);
                    texCoords.push_back(endTexCoords.x); texCoords.push_back(startTexCoords.y);
                    texCoords.push_back(startTexCoords.x); texCoords.push_back(endTexCoords.y);
                    texCoords.push_back(endTexCoords.x); texCoords.push_back(endTexCoords.y);

                    float r = tileColor.rAsFloat();
                    float g = tileColor.gAsFloat();
                    float b = tileColor.bAsFloat();
                    float a = tileColor.aAsFloat();

                    vertexColors.push_back(r); vertexColors.push_back(g); vertexColors.push_back(b); vertexColors.push_back(a);
                    vertexColors.push_back(r); vertexColors.push_back(g); vertexColors.push_back(b); vertexColors.push_back(a);
                    vertexColors.push_back(r); vertexColors.push_back(g); vertexColors.push_back(b); vertexColors.push_back(a);
                    vertexColors.push_back(r); vertexColors.push_back(g); vertexColors.push_back(b); vertexColors.push_back(a);
                    vertexColors.push_back(r); vertexColors.push_back(g); vertexColors.push_back(b); vertexColors.push_back(a);
                    vertexColors.push_back(r); vertexColors.push_back(g); vertexColors.push_back(b); vertexColors.push_back(a);
                }

                ++index;
            }
        }

        RenderEntity renderEntity;
        renderEntity.mDrawMode = GL_TRIANGLES;
        renderEntity.mElementAmount = vertices.size() / 2;

        if(vertices.size() > 0)
        {
            renderEntity.mVertexAttributes.push_back(VertexAttribute("vertex", 2, vertices));
            renderEntity.mVertexAttributes.push_back(VertexAttribute("texCoords", 2, texCoords));
            renderEntity.mVertexAttributes.push_back(VertexAttribute("colors", 4, vertexColors));
        }

        if(mTexture != nullptr)
        {
            renderEntity.mUniforms.push_back(Uniform("texture", TEXTURE, getTexture().getId()));
        }

        renderEntity.mUniforms.push_back(Uniform("position", VEC2, mPosition));
        renderEntity.mUniforms.push_back(Uniform("origin", VEC2, mOrigin));
        renderEntity.mUniforms.push_back(Uniform("rotation", FLOAT, mRotation));
        renderEntity.mUniforms.push_back(Uniform("scaling", VEC2, mScaling));
        renderEntity.mUniforms.push_back(Uniform("parallax", VEC2, mParallax));
        renderEntity.mUniforms.push_back(Uniform("constraints", VEC4, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
        glm::vec3 colorInfo = glm::vec3(mColor.rAsFloat(), mColor.gAsFloat(), mColor.bAsFloat());
        renderEntity.mUniforms.push_back(Uniform("color", VEC3, colorInfo));
        float opacity = mColor.aAsFloat();
        renderEntity.mUniforms.push_back(Uniform("opacity", FLOAT, opacity));

        for(const auto& uniform : mExtraUniforms)
            renderEntity.mUniforms.push_back(uniform.second);

        return renderEntity;
    }

    //TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth, uint32_t tileHeight, int32_t textureTileWidth, int32_t textureTileHeight, uint32_t chunkWidth, uint32_t chunkHeight)
    //{

    //    FEA_ASSERT(gridWidth > 0 && gridHeight > 0, "The size of the tile grid cannot be zero or below in any dimension! " + std::to_string(gridWidth) + " " + std::to_string(gridHeight) + " provided.");
    //    FEA_ASSERT(tileWidth > 0 && tileHeight > 0, "The size of the tiles cannot be zero or below in any dimension! " + std::to_string(tileWidth) + " " + std::to_string(tileHeight) + " provided.");
    //    FEA_ASSERT(textureTileWidth > 0.0f && textureTileHeight > 0.0f, "The size of the tiles in the texture cannot be zero or below in any dimension! " + std::to_string(textureTileWidth) + " " + std::to_string(textureTileHeight) + " provided.");
    //    FEA_ASSERT(chunkWidth > 0 && chunkHeight > 0, "The size of the tile chunks cannot be zero or below in any dimension! " + std::to_string(chunkWidth) + " " + std::to_string(chunkHeight) + " provided.");

    //    uint32_t chunkGridWidth = (gridWidth + chunkWidth - 1) / chunkWidth;
    //    uint32_t chunkGridHeight = (gridHeight + chunkHeight - 1) / chunkHeight;

    //    mChunkGridSize = glm::uvec2(chunkGridWidth, chunkGridHeight);
    //    mChunkSize = glm::uvec2(chunkWidth, chunkHeight);
    //    mGridSize = glm::uvec2(gridWidth, gridHeight);
    //    mTextureTileSize = glm::ivec2(textureTileWidth, textureTileHeight);
    //    mTileSize = glm::uvec2(tileWidth, tileHeight);

    //    bool uneven = gridWidth % chunkWidth != 0;
    //    glm::uvec2 edgeSize(gridWidth % chunkWidth, gridHeight % chunkHeight);

    //    uint32_t newChunkHeight = chunkHeight;

    //    for(uint32_t y = 0; y < chunkGridHeight; y++)
    //    {
    //        if(y == chunkGridHeight - 1 && uneven)
    //            newChunkHeight = edgeSize.y;

    //        uint32_t newChunkWidth = chunkWidth;
    //        for(uint32_t x = 0; x < chunkGridWidth; x++)
    //        {
    //            if(x == chunkGridWidth - 1 && uneven)
    //                newChunkWidth = edgeSize.x;

    //            TileChunk newChunk(newChunkWidth, newChunkHeight, tileWidth, tileHeight);
    //            glm::vec2 chunkOrigin = glm::vec2(mPosition.x +(float) (x * chunkWidth * tileWidth),mPosition.y + (float)(y * chunkHeight * tileHeight));
    //            newChunk.setOriginalOrigin(-chunkOrigin);

    //            mChunks.push_back(newChunk);
    //        }
    //    }
    //}

    //void TileMap::setPosition(const glm::vec2& pos)
    //{
    //    mPosition = pos;

    //    for(auto& chunk : mChunks)
    //        chunk.setPosition(pos);
    //}
    //
    //const glm::vec2& TileMap::getPosition() const
    //{
    //    return mPosition;
    //}

    //void TileMap::translate(const glm::vec2& amount)
    //{
    //    mPosition += amount;

    //    for(auto& chunk : mChunks)
    //        chunk.translate(amount);
    //}
    //
    //std::vector<const TileChunk*> TileMap::getTileChunks() const
    //{
    //    std::vector<const TileChunk*> toReturn;

    //    for(const auto& chunk : mChunks)
    //    {
    //        if(!chunk.isEmpty())
    //            toReturn.push_back(&chunk);
    //    }

    //    return toReturn;
    //}
    //
    //void TileMap::setTexture(const Texture& tex)
    //{
    //    mTexture = &tex;

    //    for(auto& chunk : mChunks)
    //    {
    //        chunk.setTexture(tex);
    //    }
    //}
    //
    //const Texture& TileMap::getTexture() const
    //{
    //    return *mTexture;
    //}
    //

    //void TileMap::setTile(const glm::uvec2& pos, TileId id, int32_t orientation)
    //{
    //    FEA_ASSERT(!isOutOfBounds(pos), "Trying to set tile outside of the bounds of the tilemap! Setting at " + std::to_string(pos.x) + " " + std::to_string(pos.y) + ".");
    //    FEA_ASSERT(orientation <= 16, "Cannot pass other flags with the PRESERVE flag!");
    //    uint32_t x = pos.x;
    //    uint32_t y = pos.y;

    //    uint32_t chunkX = x / mChunkSize.x;
    //    uint32_t chunkY = y / mChunkSize.y;
    //    uint32_t chunkIndex = chunkX + chunkY * mChunkGridSize.x;

    //    FEA_ASSERT(mTileDefs.find(id) != mTileDefs.end(), "Trying to set tile '" + std::to_string(id) + "' which doesn't exist!");

    //    const TileDefinition& tileDef = mTileDefs.at(id);

    //    glm::vec2 texPos = (glm::vec2)tileDef.mTileTexPosition * static_cast<glm::vec2>(mTextureTileSize);

    //    float startX = texPos.x;
    //    float startY = texPos.y;
    //    float endX   = texPos.x + mTextureTileSize.x;
    //    float endY   = texPos.y + mTextureTileSize.y;

    //    mChunks[chunkIndex].setTileTexCoords(x - chunkX * mChunkSize.x, y - chunkY * mChunkSize.y, 
    //            glm::vec2(startX , startY),
    //            glm::vec2(endX   , endY  ), orientation);

    //    if(mAnimatedTiles.find(glm::uvec2(x, y)) != mAnimatedTiles.end())
    //    {
    //        mAnimatedTiles.erase(glm::uvec2(x, y));
    //    }

    //    if(tileDef.mTicksUntilChange > 0)
    //    {
    //        AnimatedTile animation(tileDef.mNextTile, tileDef.mTicksUntilChange);
    //        mAnimatedTiles.emplace(glm::uvec2(x, y), animation);
    //    }
    //}

    //void TileMap::unsetTile(const glm::uvec2& pos)
    //{
    //    FEA_ASSERT(!isOutOfBounds(pos), "Trying to unset tile outside of the bounds of the tilemap! Setting at " + std::to_string(pos.x) + " " + std::to_string(pos.y) + ".");

    //    uint32_t x = pos.x;
    //    uint32_t y = pos.y;

    //    uint32_t chunkX = x / mChunkSize.x;
    //    uint32_t chunkY = y / mChunkSize.y;
    //    uint32_t chunkIndex = chunkX + chunkY * mChunkGridSize.x;

    //    mChunks[chunkIndex].unsetTileTexCoords(x - chunkX * mChunkSize.x, y - chunkY * mChunkSize.y);

    //    if(mAnimatedTiles.find(glm::uvec2(x, y)) != mAnimatedTiles.end())
    //    {
    //        mAnimatedTiles.erase(glm::uvec2(x, y));
    //    }
    //}

    //void TileMap::fill(TileId id)
    //{
    //    FEA_ASSERT(mTileDefs.find(id) != mTileDefs.end(), "Trying to fill tilemap with tile id  '" + std::to_string(id) + "' which doesn't exist!");

    //    const TileDefinition& tileDef = mTileDefs.at(id);

    //    glm::uvec2 texPos = tileDef.mTileTexPosition;

    //    for(auto& chunk : mChunks)
    //        chunk.fillTexCoords(glm::vec2((float)texPos.x * mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y),
    //                            glm::vec2((float)texPos.x * mTextureTileSize.x + mTextureTileSize.x, (float)texPos.y * mTextureTileSize.y + mTextureTileSize.y));

    //    mAnimatedTiles.clear();

    //    if(tileDef.mTicksUntilChange > 0)
    //    {
    //        AnimatedTile animation(tileDef.mNextTile, tileDef.mTicksUntilChange);

    //        for(uint32_t x = 0; x < mGridSize.x; x++)
    //        {
    //            for(uint32_t y = 0; y < mGridSize.y; y++)
    //            {
    //                mAnimatedTiles.emplace(glm::uvec2(x, y), animation);
    //            }
    //        }
    //    }
    //}
    //        
    //void TileMap::setTileColor(const glm::uvec2& pos, const fea::Color& color)
    //{
    //    FEA_ASSERT(!isOutOfBounds(pos), "Trying to set color outside of the bounds of the tilemap! Setting at " + std::to_string(pos.x) + " " + std::to_string(pos.y) + ".");
    //    uint32_t x = pos.x;
    //    uint32_t y = pos.y;

    //    uint32_t chunkX = x / mChunkSize.x;
    //    uint32_t chunkY = y / mChunkSize.y;
    //    uint32_t chunkIndex = chunkX + chunkY * mChunkGridSize.x;

    //    mChunks[chunkIndex].setTileColors(x - chunkX * mChunkSize.x, y - chunkY * mChunkSize.y, color);
    //}
    //
    //void TileMap::clear()
    //{
    //    for(auto& chunk : mChunks)
    //        chunk.clear();

    //    mAnimatedTiles.clear();
    //}
    //
    //glm::uvec2 TileMap::getTileSize() const
    //{
    //    return mTileSize;
    //}

    //glm::uvec2 TileMap::getGridSize() const
    //{
    //    return mGridSize;
    //}

    //glm::uvec2 TileMap::getTileMapSize() const
    //{
    //    return mTileSize * mGridSize;
    //}

    //void TileMap::tick()
    //{
    //    std::vector<glm::uvec2> toSet;
    //    std::vector<TileId> ids;

    //    for(auto animated = mAnimatedTiles.begin(); animated != mAnimatedTiles.end();)
    //    {
    //        if(animated->second.mTimeLeft == 0)
    //        {
    //            uint32_t x = animated->first.x;
    //            uint32_t y = animated->first.y;
    //            TileId id = animated->second.mNext;
    //            animated = mAnimatedTiles.erase(animated);
    //            
    //            toSet.push_back(glm::uvec2(x, y));
    //            ids.push_back(id);
    //            continue;
    //        }
    //        else
    //        {
    //            animated->second.mTimeLeft--;
    //            animated++;
    //        }
    //    }
    //    for(uint32_t i = 0; i < toSet.size(); i++)
    //    {
    //        setTile(toSet[i], ids[i], PRESERVE);
    //    }
    //}

    //void TileMap::setOpacity(float opacity)
    //{
    //    for(auto& chunk : mChunks)
    //        chunk.setOpacity(opacity);
    //}

    //float TileMap::getOpacity() const
    //{
    //    return mChunks.begin()->getOpacity();
    //}

    //void TileMap::setRotation(float rotation)
    //{
    //    for(auto& chunk : mChunks)
    //        chunk.setRotation(rotation);
    //}

    //float TileMap::getRotation() const
    //{
    //    return mChunks.begin()->getRotation();
    //}

    //void TileMap::rotate(float amount)
    //{
    //    for(auto& chunk : mChunks)
    //        chunk.rotate(amount);
    //}

    //void TileMap::setScale(const glm::vec2& scale)
    //{
    //    for(auto& chunk : mChunks)
    //    {
    //        chunk.setScale(scale);
    //        chunk.multiplyOrigin(scale);
    //    }
    //}

    //const glm::vec2& TileMap::getScale() const
    //{
    //    return mChunks.begin()->getScale();
    //}

    //void TileMap::scale(const glm::vec2& amount)
    //{
    //    for(auto& chunk : mChunks)
    //    {
    //        chunk.scale(amount);
    //        chunk.multiplyOrigin(chunk.getScale());
    //    }
    //}

    //void TileMap::setOrigin(const glm::vec2& origin)
    //{
    //    uint32_t chunkWidth = mChunkSize.x;
    //    uint32_t chunkHeight = mChunkSize.y;
    //    uint32_t chunkGridWidth = (mGridSize.x + chunkWidth - 1) / chunkWidth;
    //    uint32_t chunkGridHeight = (mGridSize.y + chunkHeight - 1) / chunkHeight;

    //    for(uint32_t y = 0; y < chunkGridHeight; y++)
    //    {
    //        for(uint32_t x = 0; x < chunkGridWidth; x++)
    //        {
    //            glm::vec2 chunkOrigin = glm::vec2(mPosition.x +(float) (x * chunkWidth * mTileSize.x),mPosition.y + (float)(y * chunkHeight * mTileSize.y));
    //            mChunks[x + y * chunkGridWidth].setOriginalOrigin(-chunkOrigin + origin);
    //        }
    //    }
    //}

    //const glm::vec2& TileMap::getOrigin() const
    //{
    //    return mChunks[0].getOrigin();
    //}

    //void TileMap::setParallax(const glm::vec2& parallax)
    //{
    //    for(auto& chunk : mChunks)
    //    {
    //        chunk.setParallax(parallax);
    //    }
    //}

    //const glm::vec2& TileMap::getParallax() const
    //{
    //    return mChunks.begin()->getParallax();
    //}

    //void TileMap::setColor(const Color& color)
    //{
    //    for(auto& chunk : mChunks)
    //    {
    //        chunk.setColor(color);
    //    }
    //}

    //Color TileMap::getColor() const
    //{
    //    return mChunks.begin()->getColor();
    //}
}
