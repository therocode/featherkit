#pragma once
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    class TileChunk : public Drawable2D
    {
        public:
            TileChunk(uint32_t width, uint32_t height, uint32_t tileWidth, uint32_t tileHeight);
            void setTexture(const std::string& tex);
            const std::string& getTexture() const;
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
        private:
            std::string textureId;
            std::vector<float> texCoords;
    };
}
