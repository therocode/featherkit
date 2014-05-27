#include <fea/rendering/tilechunk.hpp>
#include <iostream>

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
    
    void TileChunk::setTileTexCoords(uint32_t x, uint32_t y, glm::vec2 startCoords, glm::vec2 endCoords, int32_t orientation)
    {
        glm::uvec2 tile(x,y);

        auto tileIterator = mTileInfo.find(tile);

        if(tileIterator == mTileInfo.end())
        {
            size_t nextIndex = mVertices.size() / 12;
            mTileInfo.emplace(tile, std::pair<size_t, int32_t>(nextIndex, orientation));

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

            glm::vec2 coordinates[4] = {
                {startCoords.x, startCoords.y},
                {startCoords.x, endCoords.y  },
                {endCoords.x,   startCoords.y},
                {endCoords.x,   endCoords.y  }};

            if(orientation & V_FLIP)
            {
                std::swap(coordinates[0], coordinates[1]);
                std::swap(coordinates[2], coordinates[3]);
            }
            if(orientation & H_FLIP)
            {
                std::swap(coordinates[0], coordinates[2]);
                std::swap(coordinates[1], coordinates[3]);
            }

            if((orientation & 12) == 4)
            {
                std::swap(coordinates[2], coordinates[3]);
                std::swap(coordinates[0], coordinates[1]);
                std::swap(coordinates[0], coordinates[3]);
            }
            else if((orientation & 12) == 8)
            {
                std::swap(coordinates[2], coordinates[1]);
                std::swap(coordinates[0], coordinates[3]);
            }
            else if((orientation & 12) == 12)
            {
                std::swap(coordinates[2], coordinates[3]);
                std::swap(coordinates[0], coordinates[1]);
                std::swap(coordinates[1], coordinates[2]);
            }

            mTexCoords.push_back(coordinates[0].x); mTexCoords.push_back(coordinates[0].y);
            mTexCoords.push_back(coordinates[1].x); mTexCoords.push_back(coordinates[1].y);
            mTexCoords.push_back(coordinates[2].x); mTexCoords.push_back(coordinates[2].y);
            mTexCoords.push_back(coordinates[2].x); mTexCoords.push_back(coordinates[2].y);
            mTexCoords.push_back(coordinates[1].x); mTexCoords.push_back(coordinates[1].y);
            mTexCoords.push_back(coordinates[3].x); mTexCoords.push_back(coordinates[3].y);

            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
            mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f); mVertexColors.push_back(1.0f);
        }
        else
        {
            size_t texCoordIndex = tileIterator->second.first * 12;
            
            if(orientation != PRESERVE)
            {
                tileIterator->second.second = orientation;
            }
            else
            {
                orientation = tileIterator->second.second;
            }

            glm::vec2 coordinates[4] = {
                {startCoords.x, startCoords.y},
                {startCoords.x, endCoords.y  },
                {endCoords.x,   startCoords.y},
                {endCoords.x,   endCoords.y  }};

            if(orientation & V_FLIP)
            {
                std::swap(coordinates[0], coordinates[1]);
                std::swap(coordinates[2], coordinates[3]);
            }
            if(orientation & H_FLIP)
            {
                std::swap(coordinates[0], coordinates[2]);
                std::swap(coordinates[1], coordinates[3]);
            }

            if((orientation & 12) == 4)
            {
                std::swap(coordinates[2], coordinates[3]);
                std::swap(coordinates[0], coordinates[1]);
                std::swap(coordinates[0], coordinates[3]);
            }
            else if((orientation & 12) == 8)
            {
                std::swap(coordinates[2], coordinates[1]);
                std::swap(coordinates[0], coordinates[3]);
            }
            else if((orientation & 12) == 12)
            {
                std::swap(coordinates[2], coordinates[3]);
                std::swap(coordinates[0], coordinates[1]);
                std::swap(coordinates[1], coordinates[2]);
            }

            mTexCoords[texCoordIndex] =      coordinates[0].x; mTexCoords[texCoordIndex + 1] =  coordinates[0].y;
            mTexCoords[texCoordIndex + 2] =  coordinates[1].x; mTexCoords[texCoordIndex + 3] =  coordinates[1].y;
            mTexCoords[texCoordIndex + 4] =  coordinates[2].x; mTexCoords[texCoordIndex + 5] =  coordinates[2].y;
            mTexCoords[texCoordIndex + 6] =  coordinates[2].x; mTexCoords[texCoordIndex + 7] =  coordinates[2].y;
            mTexCoords[texCoordIndex + 8] =  coordinates[1].x; mTexCoords[texCoordIndex + 9] =  coordinates[1].y;
            mTexCoords[texCoordIndex + 10] = coordinates[3].x; mTexCoords[texCoordIndex + 11] = coordinates[3].y;
        }
    }
    
    void TileChunk::unsetTileTexCoords(uint32_t x, uint32_t y)
    {
        glm::uvec2 tile(x, y);

        auto tileIterator = mTileInfo.find(tile);

        if(tileIterator != mTileInfo.end())
        {
            size_t tileIndex = tileIterator->second.first;
            size_t vertexIndex = tileIndex * 12;
            size_t texCoordIndex = tileIndex * 12;
            size_t colorIndex = tileIndex * 24;

            mVertices.erase(mVertices.begin() + vertexIndex, mVertices.begin() + vertexIndex + 12);
            mTexCoords.erase(mTexCoords.begin() + texCoordIndex, mTexCoords.begin() + texCoordIndex + 12);
            mVertexColors.erase(mVertexColors.begin() + colorIndex, mVertexColors.begin() + colorIndex + 24);

            mTileInfo.erase(tile);

            for(auto& info : mTileInfo)
            {
                if(info.second.first > tileIndex)
                    info.second.first--;
            }
        }
    }
    
    void TileChunk::fillTexCoords(const glm::vec2& startCoords, const glm::vec2& endCoords)
    {
        for(size_t x = 0; x < mGridSize.x; x++)
        {
            for(size_t y = 0; y < mGridSize.y; y++)
            {
                setTileTexCoords(x, y, startCoords, endCoords, NORMAL);
            }
        }
    }
    
    void TileChunk::setTileColors(uint32_t x, uint32_t y, const fea::Color& color)
    {
        glm::uvec2 tile(x,y);

        auto tileIterator = mTileInfo.find(tile);

        if(tileIterator != mTileInfo.end())
        {
            size_t colorIndex = tileIterator->second.first * 24;

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
        mTileInfo.clear();
    }
            
    bool TileChunk::isEmpty() const
    {
        return mTileInfo.size() == 0;
    }

    std::vector<RenderEntity> TileChunk::getRenderInfo() const
    {
        std::vector<RenderEntity> temp = Drawable2D::getRenderInfo();

        temp[0].mUniforms.push_back(Uniform("texture", TEXTURE, getTexture().getId()));

        temp[0].mVertexAttributes.push_back(VertexAttribute("texCoords", 2, &mTexCoords[0]));

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
