#include <framework/rendering/tilechunk.h>

namespace windbreeze
{
    TileChunk::TileChunk(uint32_t width, uint32_t height, uint32_t tileWidth, uint32_t tileHeight)
    {
        float halfTileWidth = ((float) tileWidth) * 0.5f;
        float halfTileHeight = ((float) tileHeight) * 0.5f;

        origin = glm::vec2(0.0f, 0.0f);

        for(uint32_t y = 0; y < height; y++)
        {
            for(uint32_t x = 0; x < width; x++)
            {
                float xPos = x * tileWidth;
                float yPos = y * tileHeight;

                vertices.push_back(((float)xPos) - halfTileWidth); vertices.push_back(((float)yPos) - halfTileHeight);
                vertices.push_back(((float)xPos) - halfTileWidth); vertices.push_back(((float)yPos) + halfTileHeight);
                vertices.push_back(((float)xPos) + halfTileWidth); vertices.push_back(((float)yPos) + halfTileHeight);
                vertices.push_back(((float)xPos) + halfTileWidth); vertices.push_back(((float)yPos) - halfTileHeight);

                //texCoords.push_back(0.0f); texCoords.push_back(0.0f);
                //texCoords.push_back(0.0f); texCoords.push_back(1.0f);
                //texCoords.push_back(1.0f); texCoords.push_back(1.0f);
                //texCoords.push_back(1.0f); texCoords.push_back(0.0f);

                if(x < 5)
                {
                    texCoords.push_back(0.0f); texCoords.push_back(0.0f);
                    texCoords.push_back(0.0f); texCoords.push_back(0.25f);
                    texCoords.push_back(0.25f); texCoords.push_back(0.25f);
                    texCoords.push_back(0.25f); texCoords.push_back(0.0f);
                }
                else if(x == 5)
                {
                    texCoords.push_back(0.25f); texCoords.push_back(0.0f);
                    texCoords.push_back(0.25f); texCoords.push_back(0.25f);
                    texCoords.push_back(0.5f); texCoords.push_back(0.25f);
                    texCoords.push_back(0.5f); texCoords.push_back(0.0f);
                }
                else if(x > 5)
                {
                    texCoords.push_back(0.5f); texCoords.push_back(0.0f);
                    texCoords.push_back(0.5f); texCoords.push_back(0.25f);
                    texCoords.push_back(0.75f); texCoords.push_back(0.25f);
                    texCoords.push_back(0.75f); texCoords.push_back(0.0f);
                }
            }
        }
    }
    
    void TileChunk::setTexture(const std::string& tex)
    {
        textureId = tex;
    }

    const std::string& TileChunk::getTexture() const
    {
        return textureId;
    }

    void TileChunk::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Drawable2D::getRenderData(renderData, time);

        renderData.textureId = getTexture();

        renderData.texCoords = texCoords;
    }
}
