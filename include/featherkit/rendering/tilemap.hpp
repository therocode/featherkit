#pragma once
#include <featherkit/rendering/tilechunk.hpp>
#include <unordered_map>
#include <map>
#include <functional>

namespace fea
{
    struct TileDefinition
    {
        TileDefinition(const glm::uvec2& texPos, const std::string& next = "", uint32_t ticks = 0);
        glm::uvec2 mTileTexPosition;
        std::string mNextTile;
        uint32_t mTicksUntilChange;
    };

    class TileMap
    {
        struct AnimatedTile
        {
            AnimatedTile(const std::string& next, uint32_t timeLeft);
            std::string mNext;
            uint32_t mTimeLeft;
        };
        public:
            TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth = 16, uint32_t tileHeight = 16, float textureTileWidth = 0.25f, float textureTileHeight = 0.25f , uint32_t chunkWidth = 32, uint32_t chunkHeight = 32);
            void setPosition(const glm::vec2& position);
            const glm::vec2& getPosition() const;
            const std::vector<TileChunk>& getTileChunks() const;
            void setTexture(const Texture& texture);
            const Texture& getTexture() const;
            void addTileDefinition(const std::string& name, const TileDefinition& tileDef);
            void setTile(const glm::uvec2& pos, const std::string& name);
            void unsetTile(const glm::uvec2& pos);
            void fill(const std::string& name);
            void clear();
            glm::uvec2 getTileByCoordinates(const glm::vec2& coordinates) const;
            bool isOutOfBounds(const glm::uvec2& pos) const;
            glm::uvec2 getTileSize() const;
            glm::uvec2 getGridSize() const;
            glm::uvec2 getTileMapSize() const;
            void tick();
        private:
            glm::vec2 mPosition;
            glm::uvec2 mChunkGridSize;
            glm::uvec2 mChunkSize;
            glm::uvec2 mTileSize;
            glm::uvec2 mGridSize;
            glm::vec2 mTextureTileSize;
            std::vector<TileChunk> mChunks;
            const Texture* mTexture;
            std::unordered_map<std::string, TileDefinition> mTileDefs;
            std::map<glm::uvec2, AnimatedTile, std::function<bool(const glm::uvec2&, const glm::uvec2&)>> mAnimatedTiles;
    };
    /** @addtogroup Render2D
     *@{
     *  @struct TileDefinition
     *  @class TileMap
     *@}
     ***
     *  @struct TileDefinition
     *  @brief Data container describing a type of tile.
     *  
     *  Tile definition contains information about how a tile should be displayed and animated. The display information is coordinates of the tile texture.
     *
     *  Animation works by simply switching to a different tile definition after a set amount of ticks. For instance, if a water animation involving two different tile images of water is needed, two tile definitions, one for each desired texture must be created. They are then setup so that the first tile switches to the other after a desired amount of ticks, and the second tile switches to the first. This will naturally create a cyclic animation.
     *
     *  The animation data consists of the name of the next tile definition to switch to, and the amount of ticks it will take until the change is performed.
     ***
     *  @fn TileDefinition::TileDefinition(const glm::uvec2& texPos, const std::string& next = "", uint32_t ticks = 0)
     *  @brief Construct a TileDefinition.
     *  @param texPos Coordinates of the subrectangle to use as texture.
     *  @param next TileDefinition to change to. Only needed if the tile is animated.
     *  @param ticks Amount of ticks until the tile is changed. Only needed if the tile is animated.
     ***
     *  @var TileDefinition::mTileTexPosition
     *  @brief Coordinates describing the position of the subrect of the texture to use for this tile. For example if the map tile in the upper left corner is to be used, this variable should be (0,0). If the tile next to it is to be used, it should be (1,0).
     ***
     *  @var TileDefinition::mNextTile
     *  @brief If the tile is meant to be animated, this should be set to the name of the tile to switch to.
     ***
     *  @var TileDefinition::mTicksUntilChange
     *  @brief The amount of ticks to display this tile before it is changed to the one defined using TileDefinition::mNextTile.
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
     *
     *  Assert/undefined behavior when any of the input values are zero or below.
     *  @param gridWidth Amount of tiles on the X axis.
     *  @param gridHeight Amount of tiles on the Y axis.
     *  @param tileWidth Width of a single tile displayed on the screen in pixels with no scaling.
     *  @param tileHeight Height of a single tile displayed on the screen in pixels with no scaling.
     *  @param textureTileWidth Width of a tile in the texture image. Measured in percent of total texture width.
     *  @param textureTileHeight Height of a tile in the texture image. Measured in percent of total texture height.
     *  @param chunkWidth How many tiles on the X axis makes up a TileChunk.
     *  @param chunkHeight How many tiles on the Y axis makes up a TileChunk.
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
     *  @fn void TileMap::setTexture(const Texture& texture)
     *  @brief Set the texture to use.
     *  @param texture Texture.
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
     *  @fn void TileMap::setTile(const glm::uvec2& position, const std::string& name)
     *  @brief Set a tile at the given coordinate.
     *
     *  Assert/undefined behavior when coordinates are outside the range of the tilemap or if tile name doesn't exist.
     *  @param position Coordinate of the tile to set,
     *  @param name Name of the tile definition to change it to.
     ***
     *  @fn void TileMap::unsetTile(const glm::uvec2& pos)
     *  @brief Set a tile to be transparent.
     *  
     *  This is the default state of tiles.
     *  Assert/undefined behavior when coordinates are outside the range of the tilemap.
     *  @param pos Coordinate of the tile to unset.
     ***
     *  @fn void TileMap::fill(const std::string& name)
     *  @brief Fill the whole tile map with a single tile type.
     *
     *  Assert/undefined behavior when tile type doesn't exist.
     *  @param name Name of the tile to fill with.
     ***
     *  @fn void TileMap::clear();
     *  @brief Clear the tile map of all tiles.
     ***
     *  @fn glm::uvec2 TileMap::getTileByCoordinates(const glm::vec2& coordinates) const
     *  @brief Get the tile coordinates for the given pixel coordinate on the TileMap.
     *
     *  Assert/undefined behavior if coordinate is not within the bounds of the tilemap.
     *  @param coordinates Coordinate to check at.
     *  @return Tile coordinates.
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
