#include <featherkit/rendering/tilechunk.h>

namespace fea
{
    TileChunk::TileChunk(uint32_t width, uint32_t height, uint32_t tileWidth, uint32_t tileHeight)
    {
        float halfTileWidth = ((float) tileWidth) * 0.5f;
        float halfTileHeight = ((float) tileHeight) * 0.5f;

        mTilesSet.resize(width * height);
        std::fill(mTilesSet.begin(), mTilesSet.end(), false);

        mOrigin = glm::vec2(0.0f, 0.0f);
        mGridSize = glm::uvec2(width, height);

        for(uint32_t y = 0; y < height; y++)
        {
            for(uint32_t x = 0; x < width; x++)
            {
                float xPos = (float)(x * tileWidth) + (float)tileWidth * 0.5f;
                float yPos = (float)(y * tileHeight) + (float)tileHeight * 0.5f;

                mVerticesCached.push_back(((float)xPos) - halfTileWidth); mVerticesCached.push_back(((float)yPos) - halfTileHeight);
                mVerticesCached.push_back(((float)xPos) - halfTileWidth); mVerticesCached.push_back(((float)yPos) + halfTileHeight);
                mVerticesCached.push_back(((float)xPos) + halfTileWidth); mVerticesCached.push_back(((float)yPos) - halfTileHeight);
                mVerticesCached.push_back(((float)xPos) + halfTileWidth); mVerticesCached.push_back(((float)yPos) - halfTileHeight);
                mVerticesCached.push_back(((float)xPos) - halfTileWidth); mVerticesCached.push_back(((float)yPos) + halfTileHeight);
                mVerticesCached.push_back(((float)xPos) + halfTileWidth); mVerticesCached.push_back(((float)yPos) + halfTileHeight);

                mTexCoordsCached.push_back(0.0f); mTexCoordsCached.push_back(0.0f);
                mTexCoordsCached.push_back(0.0f); mTexCoordsCached.push_back(1.0f);
                mTexCoordsCached.push_back(1.0f); mTexCoordsCached.push_back(0.0f);
                mTexCoordsCached.push_back(1.0f); mTexCoordsCached.push_back(0.0f);
                mTexCoordsCached.push_back(0.0f); mTexCoordsCached.push_back(1.0f);
                mTexCoordsCached.push_back(1.0f); mTexCoordsCached.push_back(1.0f);

                mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f);
                mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f);
                mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f);
                mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f);
                mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f);
                mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f); mVertexColorsCached.push_back(0.0f);
            }
        }
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
        uint32_t arrayIndex = getTileIndex(x, y) * 12;

        mTexCoordsCached[arrayIndex] = startCoords.x; mTexCoordsCached[arrayIndex + 1] = startCoords.y;
        mTexCoordsCached[arrayIndex + 2] = startCoords.x; mTexCoordsCached[arrayIndex + 3] = endCoords.y;
        mTexCoordsCached[arrayIndex + 4] = endCoords.x; mTexCoordsCached[arrayIndex + 5] = startCoords.y;
        mTexCoordsCached[arrayIndex + 6] = endCoords.x; mTexCoordsCached[arrayIndex + 7] = startCoords.y;
        mTexCoordsCached[arrayIndex + 8] = startCoords.x; mTexCoordsCached[arrayIndex + 9] = endCoords.y;
        mTexCoordsCached[arrayIndex + 10] = endCoords.x; mTexCoordsCached[arrayIndex + 11] = endCoords.y;

        mTilesSet[getTileIndex(x, y)] = true;

        mTexCoords.clear();
        mVertexColors.clear();
        mVertices.clear();

        for(uint32_t yy = 0; yy < mGridSize.y; yy++)
        {
            for(uint32_t xx = 0; xx < mGridSize.x; xx++)
            {
                uint32_t index = getTileIndex(xx, yy);
                if(mTilesSet[index])
                {
                    mTexCoords.insert(mTexCoords.end(), mTexCoordsCached.begin() + index * 12, mTexCoordsCached.begin() + index * 12 + 12);
                    mVertexColors.insert(mVertexColors.end(), mVertexColorsCached.begin() + index * 24, mVertexColorsCached.begin() + index * 24 + 24);
                    mVertices.insert(mVertices.end(), mVerticesCached.begin() + index * 12, mVerticesCached.begin() + index * 12 + 12);
                }
            }
        }
    }
    
    void TileChunk::unsetTileTexCoords(uint32_t x, uint32_t y)
    {
        mTilesSet[getTileIndex(x, y)] = false;

        mTexCoords.clear();
        mVertexColors.clear();
        mVertices.clear();

        for(uint32_t yy = 0; yy < mGridSize.y; yy++)
        {
            for(uint32_t xx = 0; xx < mGridSize.x; xx++)
            {
                uint32_t index = getTileIndex(xx, yy);
                if(mTilesSet[index])
                {
                    mTexCoords.insert(mTexCoords.end(), mTexCoordsCached.begin() + index * 12, mTexCoordsCached.begin() + index * 12 + 12);
                    mVertexColors.insert(mVertexColors.end(), mVertexColorsCached.begin() + index * 24, mVertexColorsCached.begin() + index * 24 + 24);
                    mVertices.insert(mVertices.end(), mVerticesCached.begin() + index * 12, mVerticesCached.begin() + index * 12 + 12);
                }
            }
        }
    }
    
    void TileChunk::fillTexCoords(const glm::vec2& startCoords, const glm::vec2& endCoords)
    {
        std::fill(mTilesSet.begin(), mTilesSet.end(), true);

        uint32_t total = mGridSize.x * mGridSize.y * 12;
        for(uint32_t i = 0; i < total; i += 12)
        {
            mTexCoordsCached[i] = startCoords.x; mTexCoordsCached[i + 1] = startCoords.y;
            mTexCoordsCached[i + 2] = startCoords.x; mTexCoordsCached[i + 3] = endCoords.y;
            mTexCoordsCached[i + 4] = endCoords.x; mTexCoordsCached[i + 5] = startCoords.y;
            mTexCoordsCached[i + 6] = endCoords.x; mTexCoordsCached[i + 7] = startCoords.y;
            mTexCoordsCached[i + 8] = startCoords.x; mTexCoordsCached[i + 9] = endCoords.y;
            mTexCoordsCached[i + 10] = endCoords.x; mTexCoordsCached[i + 11] = endCoords.y;
        }

        mTexCoords = mTexCoordsCached;
        mVertexColors = mVertexColorsCached;
        mVertices = mVerticesCached;
    }
    
    void TileChunk::clear()
    {
        std::fill(mTilesSet.begin(), mTilesSet.end(), false);

        mTexCoords.clear();
        mVertexColors.clear();
        mVertices.clear();
    }

    RenderInfo TileChunk::getRenderInfo() const
    {
        RenderInfo temp = Drawable2D::getRenderInfo();
        std::hash<std::string> stringHasher;

        temp.mUniforms.push_back(Uniform(stringHasher("texture"), TEXTURE, getTexture().getId()));

        temp.mVertexAttributes.push_back(VertexAttribute(stringHasher("texCoords"), 2, &mTexCoords[0]));

        return temp;
    }
    
    uint32_t TileChunk::getTileIndex(uint32_t x, uint32_t y)
    {
        return x + y * mGridSize.x;
    }
}
