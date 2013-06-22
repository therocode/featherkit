#pragma once
#include <framework/rendering/tilechunk.h>
#include <map>
#include <unordered_map>
#include <functional>

namespace windbreeze
{
    using TileId = size_t;
    struct TileDefinition
    {
        TileDefinition(glm::uvec2 texPos, TileId nextId = 0, uint32_t ticks = 0);
        glm::uvec2 tileTexPosition;
        TileId nextTileId;
        uint32_t ticksUntilChange;
    };

    class TileMapException : public std::runtime_error 
    {
        public:
            TileMapException(const std::string& message) 
                : std::runtime_error(message) { };
    };


    class TileMap
    {
        struct AnimatedTile
        {
            TileId next;
            uint32_t timeLeft;
        };
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
            TileId getTileId(const std::string& name);
            glm::uvec2 getTileByCoordinates(float x, float y);
            bool isOutOfBounds(uint32_t x, uint32_t y);
            void tick();
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
            std::map<glm::uvec2, AnimatedTile, std::function<bool(const glm::uvec2&, const glm::uvec2&)> > animatedTiles { [](const glm::uvec2& first, const glm::uvec2& second){ 
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
           } };
    };
}
