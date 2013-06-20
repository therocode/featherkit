#pragma once
#include <framework/rendering/tilechunk.h>

namespace windbreeze
{
    class TileMap
    {
        public:
            TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth = 16, uint32_t tileHeight = 16, float textureTileWidth = 0.25f, float textureTileHeight = 0.25f , uint32_t chunkWidth = 16, uint32_t chunkHeight = 16);
            void setPosition(const glm::vec2& pos);
            const glm::vec2& getPosition() const;
            const std::vector<TileChunk>& getTileChunks() const;
            void setTexture(const std::string& name);
            const std::string& getTexture() const;
        private:
            glm::vec2 position;
            glm::uvec2 chunkGridSize;
            std::vector<TileChunk> chunks;
            std::string textureId;
    };
}
