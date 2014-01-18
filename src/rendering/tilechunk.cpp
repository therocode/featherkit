#include <featherkit/rendering/tilechunk.h>

namespace fea
{
    TileChunk::TileChunk(uint32_t width, uint32_t height, uint32_t tileWidth, uint32_t tileHeight)
    {
        float halfTileWidth = ((float) tileWidth) * 0.5f;
        float halfTileHeight = ((float) tileHeight) * 0.5f;

        tilesSet.resize(width * height);
        std::fill(tilesSet.begin(), tilesSet.end(), false);

        origin = glm::vec2(0.0f, 0.0f);
        gridSize = glm::uvec2(width, height);

        for(uint32_t y = 0; y < height; y++)
        {
            for(uint32_t x = 0; x < width; x++)
            {
                float xPos = (float)(x * tileWidth) + (float)tileWidth * 0.5f;
                float yPos = (float)(y * tileHeight) + (float)tileHeight * 0.5f;

                verticesCached.push_back(((float)xPos) - halfTileWidth); verticesCached.push_back(((float)yPos) - halfTileHeight);
                verticesCached.push_back(((float)xPos) - halfTileWidth); verticesCached.push_back(((float)yPos) + halfTileHeight);
                verticesCached.push_back(((float)xPos) + halfTileWidth); verticesCached.push_back(((float)yPos) - halfTileHeight);
                verticesCached.push_back(((float)xPos) + halfTileWidth); verticesCached.push_back(((float)yPos) - halfTileHeight);
                verticesCached.push_back(((float)xPos) - halfTileWidth); verticesCached.push_back(((float)yPos) + halfTileHeight);
                verticesCached.push_back(((float)xPos) + halfTileWidth); verticesCached.push_back(((float)yPos) + halfTileHeight);

                texCoordsCached.push_back(0.0f); texCoordsCached.push_back(0.0f);
                texCoordsCached.push_back(0.0f); texCoordsCached.push_back(1.0f);
                texCoordsCached.push_back(1.0f); texCoordsCached.push_back(0.0f);
                texCoordsCached.push_back(1.0f); texCoordsCached.push_back(0.0f);
                texCoordsCached.push_back(0.0f); texCoordsCached.push_back(1.0f);
                texCoordsCached.push_back(1.0f); texCoordsCached.push_back(1.0f);

                vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f);
                vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f);
                vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f);
                vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f);
                vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f);
                vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f); vertexColoursCached.push_back(0.0f);
            }
        }
        drawMode = GL_TRIANGLES;
    }
    
    void TileChunk::setTexture(const Texture& tex)
    {
        texture = &tex;
    }

    const Texture& TileChunk::getTexture() const
    {
        return *texture;
    }
    
    void TileChunk::setTileTexCoords(uint32_t x, uint32_t y, const glm::vec2& startCoords, const glm::vec2& endCoords)
    {
        uint32_t arrayIndex = getTileIndex(x, y) * 12;

        texCoordsCached[arrayIndex] = startCoords.x; texCoordsCached[arrayIndex + 1] = startCoords.y;
        texCoordsCached[arrayIndex + 2] = startCoords.x; texCoordsCached[arrayIndex + 3] = endCoords.y;
        texCoordsCached[arrayIndex + 4] = endCoords.x; texCoordsCached[arrayIndex + 5] = startCoords.y;
        texCoordsCached[arrayIndex + 6] = endCoords.x; texCoordsCached[arrayIndex + 7] = startCoords.y;
        texCoordsCached[arrayIndex + 8] = startCoords.x; texCoordsCached[arrayIndex + 9] = endCoords.y;
        texCoordsCached[arrayIndex + 10] = endCoords.x; texCoordsCached[arrayIndex + 11] = endCoords.y;

        tilesSet[getTileIndex(x, y)] = true;

        texCoords.clear();
        vertexColours.clear();
        vertices.clear();

        for(uint32_t yy = 0; yy < gridSize.y; yy++)
        {
            for(uint32_t xx = 0; xx < gridSize.x; xx++)
            {
                uint32_t index = getTileIndex(xx, yy);
                if(tilesSet[index])
                {
                    texCoords.insert(texCoords.end(), texCoordsCached.begin() + index * 12, texCoordsCached.begin() + index * 12 + 12);
                    vertexColours.insert(vertexColours.end(), vertexColoursCached.begin() + index * 24, vertexColoursCached.begin() + index * 24 + 24);
                    vertices.insert(vertices.end(), verticesCached.begin() + index * 12, verticesCached.begin() + index * 12 + 12);
                }
            }
        }
    }
    
    void TileChunk::unsetTileTexCoords(uint32_t x, uint32_t y)
    {
        tilesSet[getTileIndex(x, y)] = false;

        texCoords.clear();
        vertexColours.clear();
        vertices.clear();

        for(uint32_t yy = 0; yy < gridSize.y; yy++)
        {
            for(uint32_t xx = 0; xx < gridSize.x; xx++)
            {
                uint32_t index = getTileIndex(xx, yy);
                if(tilesSet[index])
                {
                    texCoords.insert(texCoords.end(), texCoordsCached.begin() + index * 12, texCoordsCached.begin() + index * 12 + 12);
                    vertexColours.insert(vertexColours.end(), vertexColoursCached.begin() + index * 24, vertexColoursCached.begin() + index * 24 + 24);
                    vertices.insert(vertices.end(), verticesCached.begin() + index * 12, verticesCached.begin() + index * 12 + 12);
                }
            }
        }
    }
    
    void TileChunk::fillTexCoords(const glm::vec2& startCoords, const glm::vec2& endCoords)
    {
        std::fill(tilesSet.begin(), tilesSet.end(), true);

        uint32_t total = gridSize.x * gridSize.y * 12;
        for(uint32_t i = 0; i < total; i += 12)
        {
            texCoordsCached[i] = startCoords.x; texCoordsCached[i + 1] = startCoords.y;
            texCoordsCached[i + 2] = startCoords.x; texCoordsCached[i + 3] = endCoords.y;
            texCoordsCached[i + 4] = endCoords.x; texCoordsCached[i + 5] = startCoords.y;
            texCoordsCached[i + 6] = endCoords.x; texCoordsCached[i + 7] = startCoords.y;
            texCoordsCached[i + 8] = startCoords.x; texCoordsCached[i + 9] = endCoords.y;
            texCoordsCached[i + 10] = endCoords.x; texCoordsCached[i + 11] = endCoords.y;
        }

        texCoords = texCoordsCached;
        vertexColours = vertexColoursCached;
        vertices = verticesCached;
    }
    
    void TileChunk::clear()
    {
        std::fill(tilesSet.begin(), tilesSet.end(), false);

        texCoords.clear();
        vertexColours.clear();
        vertices.clear();
    }

    RenderInfo TileChunk::getRenderInfo() const
    {
        RenderInfo temp = Drawable2D::getRenderInfo();
        std::hash<std::string> stringHasher;

        temp.uniforms.push_back(Uniform(stringHasher("texture"), TEXTURE, getTexture().getId()));

        temp.vertexAttributes.push_back(VertexAttribute(stringHasher("texCoords"), 2, &texCoords[0]));

        return temp;
    }
    
    uint32_t TileChunk::getTileIndex(uint32_t x, uint32_t y)
    {
        return x + y * gridSize.x;
    }
}
