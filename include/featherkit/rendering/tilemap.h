#pragma once
#include <featherkit/rendering/tilechunk.h>
#include <map>
#include <unordered_map>
#include <functional>
#include <stdexcept>

namespace fea
{
    using TileId = size_t;
    struct TileDefinition
    {
        TileDefinition(glm::uvec2 texPos, TileId nextId = 0, uint32_t ticks = 0);
        TileDefinition(uint32_t texX, uint32_t texY, TileId nextId = 0, uint32_t ticks = 0);
        glm::uvec2 tileTexPosition;
        TileId nextTileId;
        uint32_t ticksUntilChange;
    };

    class TileMapException : public std::runtime_error 
    {
        public:
            TileMapException(const std::string& message);
    };


    class TileMap
    {
        struct AnimatedTile
        {
            TileId next;
            uint32_t timeLeft;
        };
        public:
            TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth = 16, uint32_t tileHeight = 16, float textureTileWidth = 0.25f, float textureTileHeight = 0.25f , uint32_t chunkWidth = 32, uint32_t chunkHeight = 32);
            void setPosition(float x, float y);
            void setPosition(const glm::vec2& position);
            const glm::vec2& getPosition() const;
            const std::vector<TileChunk>& getTileChunks() const;
            void setTexture(const Texture& tex);
            const Texture& getTexture() const;
            void addTileDefinition(const std::string& name, const TileDefinition& tileDef);
            void setTileByName(uint32_t x, uint32_t y, std::string name);
            void setTileByName(const glm::uvec2& pos, std::string name);
            void setTileById(uint32_t x, uint32_t y, TileId id);
            void setTileById(const glm::uvec2& pos, TileId id);
            TileId getTileId(const std::string& name) const;
            glm::uvec2 getTileByCoordinates(float x, float y) const;
            glm::uvec2 getTileByCoordinates(const glm::vec2& coordinates) const;
            bool isOutOfBounds(uint32_t x, uint32_t y) const;
            bool isOutOfBounds(const glm::uvec2& pos) const;
            glm::uvec2 getTileSize() const;
            glm::uvec2 getGridSize() const;
            glm::uvec2 getTileMapSize() const;
            void tick();
        private:
            glm::vec2 position;
            glm::uvec2 chunkGridSize;
            glm::uvec2 chunkSize;
            glm::uvec2 tileSize;
            glm::uvec2 gridSize;
            glm::vec2 textureTileSize;
            std::vector<TileChunk> chunks;
            const Texture* texture;
            std::unordered_map<TileId, TileDefinition> tileDefs;
            std::hash<std::string> hasher;
            std::map<glm::uvec2, AnimatedTile, std::function<bool(const glm::uvec2&, const glm::uvec2&)> > animatedTiles;
    };
    /** @addtogroup Render2D
     *@{
     *  @struct TileDefinition
     *  @class TileMapException
     *  @class TileMap
     *@}
     ***
     *  @struct TileDefinition
     *  @brief Data container describing a type of tile.
     *  
     *  Tile definition contains information about how a tile should be displayed and animated. The display information is texture coordinates of the tile texture.
     *
     *  Animation works by simply switching to a different tile definition after a set amount of ticks. For instance, if a water animation involving two different tile images of water is needed, two tile definitions, one for each desired texture must be created. They are then setup so that the first tile switches to the other after a desired amount of ticks, and the second tile switches to the first. This will naturally create a cyclic animation.
     *
     *  The animation data consists of the ID of the next tile definition to switch to, and the amount of ticks it will take until the change is performed.
     ***
     *  @fn TileDefinition::TileDefinition(glm::uvec2 texPos, TileId nextId = 0, uint32_t ticks = 0)
     *  @brief Construct a TileDefinition.
     *  @param texPos Texture coordinates of the tile.
     *  @param nextId TileDefinition to change to. Only needed if the tile is animated.
     *  @param ticks Amount of ticks until the tile is changed. Only needed if the tile is animated.
     ***
     *  @fn TileDefinition::TileDefinition(uint32_t texX, uint32_t texY, TileId nextId = 0, uint32_t ticks = 0)
     *  @brief Construct a TileDefinition.
     *  @param texX X Texture coordinates of the tile.
     *  @param texY Y Texture coordinates of the tile.
     *  @param nextId TileDefinition to change to. Only needed if the tile is animated.
     *  @param ticks Amount of ticks until the tile is changed. Only needed if the tile is animated.
     ***
     *  @var TileDefinition::tileTexPosition
     *  @brief Texture coordinates describing the top-left corner of a tile in a tile map texture.
     ***
     *  @var TileDefinition::nextTileId
     *  @brief If the tile is meant to be animated, this should be set to the ID of the tile to switch to.
     ***
     *  @var TileDefinition::ticksUntilChange
     *  @brief The amount of ticks to display this tile before it is changed to the one defined using TileDefinition::nextTileId.
     *
     *  Texts can be scaled and positioned, but not rotated.
     ***
     *  @fn Text::Text(const std::string& t)
     *  @brief Construct a Text drawable with the given string.
     *  @param t Text string.
     ***
     *  @class TileMapException
     *  @brief Exception used by the TileMap when something goes wrong.
     ***
     *  @fn TileMapException::TileMapException(const std::string& message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
     ***
     *  @class TileMap
     *  @brief Represents a graphical tile map with tiles that can be set freely and animated.
     *  
     *  Both the size of the grid and the individual tiles is customisable.
     *  
     *  This class is not a Drawable2D and can therefore not be rendered directly. It internally manages TileChunk instances which the whole tilemap is divided into. These have to be sent to the renderer for rendering. The size of the tile chunks is customisable.
     ***
     *  @fn TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth = 16, uint32_t tileHeight = 16, float textureTileWidth = 0.25f, float textureTileHeight = 0.25f , uint32_t chunkWidth = 32, uint32_t chunkHeight = 32)
     *  @brief Construct a TileMap.
     *  @param gridWidth Amount of tiles on the X axis.
     *  @param gridHeight Amount of tiles on the Y axis.
     *  @param tileWidth Width of a single tile displayed on the screen in pixels with no scaling.
     *  @param tileHeight Height of a single tile displayed on the screen in pixels with no scaling.
     *  @param textureTileWidth Width of a tile in the texture image. Measured in percent of total texture width.
     *  @param textureTileHeight Height of a tile in the texture image. Measured in percent of total texture height.
     *  @param chunkWidth How many tiles on the X axis makes up a TileChunk.
     *  @param chunkHeight How many tiles on the Y axis makes up a TileChunk.
     ***
     *  @fn void TileMap::setPosition(float x, float y)
     *  @brief Set the position.
     *  @param x X position.
     *  @param y Y position.
     ***
     *  @fn void TileMap::setPosition(const glm::vec2& position)
     *  @brief Set the position.
     *  @param position Vector containing the position.
     ***
     *  @fn const glm::vec2& TileMap::getPosition() const
     *  @brief Get the position.
     *  @return Vector containing the position.
     ***
     *  @fn const std::vector<TileChunk>& TileMap::getTileChunks() const
     *  @brief Get a list of all TileChunk instances making up the TileMap. 
     *
     *  This function is what is used to render the TileMap. The list of the TileChunk instances can be iterated through, to pass the content to the rendered.
     *  @return List of tile chunks.
     ***
     *  @fn void TileMap::setTexture(const std::string& name)
     *  @brief Set the texture to use.
     *  @param name Name of the texture.
     ***
     *  @fn const std::string& TileMap::getTexture() const
     *  @brief Get the current texture.
     *  @return Name of the texture.
     ***
     *  @fn void TileMap::addTileDefinition(const std::string& name, const TileDefinition& tileDef)
     *  @brief Add a new tile definition.
     *  
     *  Before a tile is set, its type has to be registered with the TileMap using this function. It can then be accessed through the given name.
     *  @param name Name of the tile to add.
     *  @param tileDef Tile definition.
     ***
     *  @fn void TileMap::setTileByName(uint32_t x, uint32_t y, std::string name)
     *  @brief Set a tile at the given coordinate.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     *  @param name Name of the tile definition to change it to.
     ***
     *  @fn void TileMap::setTileByName(const glm::uvec2& position, std::string name)
     *  @brief Set a tile at the given coordinate.
     *  @param position Coordinate of the tile to set,
     *  @param name Name of the tile definition to change it to.
     ***
     *  @fn void TileMap::setTileById(uint32_t x, uint32_t y, TileId id)
     *  @brief Set a tile at the given coordinate.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     *  @param id ID of the tile definition to change to.
     ***
     *  @fn void TileMap::setTileById(const glm::uvec2& position, TileId id)
     *  @brief Set a tile at the given coordinate.
     *  @param position Coordinate of the tile to set.
     *  @param id ID of the tile definition to change to.
     ***
     *  @fn TileId TileMap::getTileId(const std::string& name) const
     *  @brief Get the registered tile definition ID for the given name.
     *  @param name Name to check the ID for.
     *  @return The tile definition ID.
     ***
     *  @fn glm::uvec2 TileMap::getTileByCoordinates(float x, float y) const
     *  @brief Get the tile coordinates for the given pixel coordinate on the TileMap.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     *  @return Tile coordinates.
     ***
     *  @fn glm::uvec2 TileMap::getTileByCoordinates(const glm::vec2& coordinates) const
     *  @brief Get the tile coordinates for the given pixel coordinate on the TileMap.
     *  @param coordinates Coordinate to check at.
     *  @return Tile coordinates.
     ***
     *  @fn bool TileMap::isOutOfBounds(uint32_t x, uint32_t y) const
     *  @brief Checks if a tile is out of bounds.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     *  @return True if the given tile coordinate is not within the tile grid.
     ***
     *  @fn bool TileMap::isOutOfBounds(const glm::uvec2& position) const
     *  @brief Checks if a tile is out of bounds.
     *  @param position Coordinate.
     *  @return True if the given tile coordinate is not within the tile grid.
     ***
     *  @fn void TileMap::tick()
     *  @brief Advance the animation clock by one step.
     *  
     *  This function needs to be called once every frame for the animations to work properly
     ***
     *  @fn glm::uvec2 TileMap::getTileSize() const
     *  @brief Get the size of a single tile.
     *  @return The tile size.
     ***
     *  @fn glm::uvec2 TileMap::getGridSize() const
     *  @brief Get the dimensions of the grid in tiles.
     *  @return The size of the grid.
     ***
     *  @fn glm::uvec2 TileMap::getTileMapSize() const
     *  @brief Get the total size of the whole tilemap.
     *  
     *  This will return the size of a single tile multiplied with the tile grid dimensions.
     *  @return Total size of the tilemap.
     ***/
}
