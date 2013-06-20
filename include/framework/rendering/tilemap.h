#pragma once
#include <framework/rendering/tilechunk.h>
#include <unordered_map>

namespace windbreeze
{
    using TileId = size_t;

    struct TileDefinition
    {
        glm::uvec2 tileTexPosition;
    };

    class TileMap
    {
        public:
            TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth = 16, uint32_t tileHeight = 16, float textureTileWidth = 0.25f, float textureTileHeight = 0.25f , uint32_t chunkWidth = 16, uint32_t chunkHeight = 16);
            void setPosition(const glm::vec2& pos);
            const glm::vec2& getPosition() const;
            const std::vector<TileChunk>& getTileChunks() const;
            void setTexture(const std::string& name);
            const std::string& getTexture() const;
            void addTileDefinition(const std::string& name, const TileDefinition& tileDef);
            void setTileByName(uint32_t x, uint32_t y, std::string name);
            void setTileById(uint32_t x, uint32_t y, TileId id);
            glm::uvec2 getTileByCoordinates(float x, float y);
            bool isOutOfBounds(uint32_t x, uint32_t y);
        private:
            glm::vec2 position;
            glm::uvec2 chunkGridSize;
            glm::uvec2 chunkSize;
            glm::uvec2 tileSize;
            glm::uvec2 gridSize;
            glm::vec2 textureTileSize;
            std::vector<TileChunk> chunks;
            std::string textureId;
            std::unordered_map<TileId, TileDefinition> tileDefs;
            std::hash<std::string> hasher;
    };
}
