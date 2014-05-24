#include <fea/rendering/tilechunk.hpp>

namespace fea
{
    TileChunk::TileChunk(uint32_t width, uint32_t height, uint32_t tileWidth, uint32_t tileHeight):
        mTileSize(tileWidth, tileHeight)
    {
        mOrigin = glm::vec2(0.0f, 0.0f);
        mGridSize = glm::uvec2(width, height);

        mDrawMode = GL_TRIANGLES;
    }
    
    void TileChunk::setTexture(const Texture& tex)
    {
        mTexture = &tex;
    }

    const Texture& TileChunk::getTexture() const
    {
        return *mTexture;
    }
    
    void TileChunk::setTileTexCoords(uint32_t x, uint32_t y, const glm::vec2& startCoords, const glm::vec2& endCoords)
    {
        glm::uvec2 tile(x,y);

        auto tileIterator = mTileIndices.find(tile);

        if(tileIterator == mTileIndices.end())
        {
            size_t nextIndex = mVertices.size() / 12;
            mTileIndices.emplace(tile, nextIndex);

            float xPos = (float)(x * mTileSize.x) + (float)mTileSize.x * 0.5f;
            float yPos = (float)(y * mTileSize.y) + (float)mTileSize.y * 0.5f;
            float halfTileWidth = ((float) mTileSize.x) * 0.5f;
            float halfTileHeight = ((float) mTileSize.y) * 0.5f;

            mVertices.push_back(((float)xPos) - halfTileWidth); mVertices.push_back(((float)yPos) - halfTileHeight);
            mVertices.push_back(((float)xPos) - halfTileWidth); mVertices.push_back(((float)yPos) + halfTileHeight);
            mVertices.push_back(((float)xPos) + halfTileWidth); mVertices.push_back(((float)yPos) - halfTileHeight);
            mVertices.push_back(((float)xPos) + halfTileWidth); mVertices.push_back(((float)yPos) - halfTileHeight);
            mVertices.push_back(((float)xPos) - halfTileWidth); mVertices.push_back(((float)yPos) + halfTileHeight);
            mVertices.push_back(((float)xPos) + halfTileWidth); mVertices.push_back(((float)yPos) + halfTileHeight);

            mTexCoords.push_back(startCoords.x); mTexCoords.push_back(startCoords.y);
            mTexCoords.push_back(startCoords.x); mTexCoords.push_back(endCoords.y  );
            mTexCoords.push_back(endCoords.x  ); mTexCoords.push_back(startCoords.y);
            mTexCoords.push_back(endCoords.x  ); mTexCoords.push_back(startCoords.y);
            mTexCoords.push_back(startCoords.x); mTexCoords.push_back(endCoords.y  );
            mTexCoords.push_back(endCoords.x  ); mTexCoords.push_back(endCoords.y  );

            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
        }
        else
        {
            size_t texCoordIndex = tileIterator->second * 12;

            mTexCoords[texCoordIndex] =      startCoords.x; mTexCoords[texCoordIndex + 1] =  startCoords.y;
            mTexCoords[texCoordIndex + 2] =  startCoords.x; mTexCoords[texCoordIndex + 3] =  endCoords.y;
            mTexCoords[texCoordIndex + 4] =  endCoords.x;   mTexCoords[texCoordIndex + 5] =  startCoords.y;
            mTexCoords[texCoordIndex + 6] =  endCoords.x;   mTexCoords[texCoordIndex + 7] =  startCoords.y;
            mTexCoords[texCoordIndex + 8] =  startCoords.x; mTexCoords[texCoordIndex + 9] =  endCoords.y;
            mTexCoords[texCoordIndex + 10] = endCoords.x;   mTexCoords[texCoordIndex + 11] = endCoords.y;
        }
    }
    
    void TileChunk::unsetTileTexCoords(uint32_t x, uint32_t y)
    {
        glm::uvec2 tile(x, y);

        auto tileIterator = mTileIndices.find(tile);

        if(tileIterator != mTileIndices.end())
        {
            size_t tileIndex = tileIterator->second;
            size_t vertexIndex = tileIndex * 12;
            size_t texCoordIndex = tileIndex * 12;
            size_t colorIndex = tileIndex * 24;

            mVertices.erase(mVertices.begin() + vertexIndex, mVertices.begin() + vertexIndex + 12);
            mTexCoords.erase(mTexCoords.begin() + texCoordIndex, mTexCoords.begin() + texCoordIndex + 12);
            mVertexColors.erase(mVertexColors.begin() + colorIndex, mVertexColors.begin() + colorIndex + 24);

            mTileIndices.erase(tile);

            for(auto& index : mTileIndices)
            {
                if(index.second > tileIndex)
                    index.second--;
            }
        }
    }
    
    void TileChunk::fillTexCoords(const glm::vec2& startCoords, const glm::vec2& endCoords)
    {
        for(size_t x = 0; x < mGridSize.x; x++)
        {
            for(size_t y = 0; y < mGridSize.y; y++)
            {
                setTileTexCoords(x, y, startCoords, endCoords);
            }
        }
    }
    
    void TileChunk::setTileColors(uint32_t x, uint32_t y, const fea::Color& color)
    {
        glm::uvec2 tile(x,y);

        auto tileIterator = mTileIndices.find(tile);

        if(tileIterator != mTileIndices.end())
        {
            size_t colorIndex = tileIterator->second * 24;

            mVertexColors[colorIndex] = color.r(); mVertexColors[colorIndex + 1] = color.g(); mVertexColors[colorIndex + 2] = color.b(); mVertexColors[colorIndex + 3] = color.a();
            mVertexColors[colorIndex + 4] = color.r(); mVertexColors[colorIndex + 5] = color.g(); mVertexColors[colorIndex + 6] = color.b(); mVertexColors[colorIndex + 7] = color.a();
            mVertexColors[colorIndex + 8] = color.r(); mVertexColors[colorIndex + 9] = color.g(); mVertexColors[colorIndex + 10] = color.b(); mVertexColors[colorIndex + 11] = color.a();
            mVertexColors[colorIndex + 12] = color.r(); mVertexColors[colorIndex + 13] = color.g(); mVertexColors[colorIndex + 14] = color.b(); mVertexColors[colorIndex + 15] = color.a();
            mVertexColors[colorIndex + 16] = color.r(); mVertexColors[colorIndex + 17] = color.g(); mVertexColors[colorIndex + 18] = color.b(); mVertexColors[colorIndex + 19] = color.a();
            mVertexColors[colorIndex + 20] = color.r(); mVertexColors[colorIndex + 21] = color.g(); mVertexColors[colorIndex + 22] = color.b(); mVertexColors[colorIndex + 23] = color.a();
        }
    }
    
    void TileChunk::clear()
    {
        mTexCoords.clear();
        mVertexColors.clear();
        mVertices.clear();
        mTileIndices.clear();
    }
            
    bool TileChunk::isEmpty() const
    {
        return mTileIndices.size() == 0;
    }

    RenderInfo TileChunk::getRenderInfo() const
    {
        RenderInfo temp = Drawable2D::getRenderInfo();

        temp.mUniforms.push_back(Uniform("texture", TEXTURE, getTexture().getId()));

        temp.mVertexAttributes.push_back(VertexAttribute("texCoords", 2, &mTexCoords[0]));

        return temp;
    }
    
    void TileChunk::setOriginalOrigin(const glm::vec2& origin)
    {
        mOriginalOrigin = origin;
        setOrigin(origin);
    }

    void TileChunk::multiplyOrigin(const glm::vec2& mult)
    {
        setOrigin(mOriginalOrigin * mult);
    }

    uint32_t TileChunk::getTileIndex(uint32_t x, uint32_t y)
    {
        return x + y * mGridSize.x;
    }
}
