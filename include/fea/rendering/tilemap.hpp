#pragma once
#include <fea/config.hpp>
#include <unordered_map>
#include <functional>
#include <fea/rendering/glmhash.hpp>
#include <fea/rendering/drawable2d.hpp>
#include <fea/rendering/texture.hpp>

namespace fea
{
    using TileId = int32_t;

    struct FEA_API TileDefinition
    {
        TileDefinition(const glm::ivec2& texPos, TileId next = -1, int32_t ticks = 1);
        glm::ivec2 tileTexPosition;
        TileId nextTile;
        int32_t ticksUntilChange;
    };

    class FEA_API TileMap: public fea::Drawable2D
    {
        struct Tile
        {
            TileId id;
            fea::Color color;
            int32_t ticksUntilChange;
        };

        struct TileChunk
        {
            TileChunk();
            void setTile(const glm::ivec2& position, TileId id);
            void setTileColor(const glm::ivec2& position, const fea::Color& color);
            void unsetTile(const glm::ivec2& position);
            const Tile& getTile(const glm::ivec2& position) const;
            Tile& getTile(const glm::ivec2& position);
            int32_t tileCount;
            std::vector<Tile> tiles;
            std::vector<bool> tilesSet;
        };

        public:
        TileMap(const glm::ivec2& tileSize, const glm::ivec2& tileTextureSize);
        void setTexture(const Texture& texture);
        const Texture& getTexture() const;
        void addTileDefinition(TileId id, const TileDefinition& tileDef);
        void setTile(const glm::ivec2& pos, TileId id);
        void unsetTile(const glm::ivec2& pos);
        void fillRegion(glm::ivec2 startCorner, glm::ivec2 endCorner, TileId id);
        void clear();
        void setTileColor(const glm::ivec2& pos, const fea::Color& color);
        const Tile& getTile(const glm::ivec2& pos) const;
        glm::ivec2 worldToTileCoordinates(const glm::vec2& coordinates) const;
        const glm::ivec2& getTileSize() const;
        const glm::ivec2& getTileTextureSize() const;
        void tick();
        virtual std::vector<RenderEntity> getRenderInfo() const override;
        private:
        glm::ivec2 tileToChunk(const glm::ivec2& pos) const;
        glm::ivec2 tileToTileInChunk(const glm::ivec2& pos) const;
        RenderEntity renderInfoFromChunk(const glm::ivec2& chunkPos, const TileChunk& chunk) const;
        glm::ivec2 mTileSize;
        glm::ivec2 mTileTextureSize;
        const Texture* mTexture;

        std::unordered_map<TileId, TileDefinition> mTileDefinitions;
        std::unordered_map<glm::ivec2, TileChunk> mChunks;
        std::unordered_map<glm::ivec2, Tile*> mAnimatedTiles;
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
     *  @fn TileDefinition::TileDefinition(const glm::uvec2& texPos, TileId next = "", uint32_t ticks = 0)
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
     *  This class is not a TileMap and can therefore not be rendered directly. It internally manages TileChunk instances which the whole tilemap is divided into. These have to be sent to the renderer for rendering. The size of the tile chunks is customisable.
     ***
     *  @fn TileMap::TileMap(uint32_t gridWidth, uint32_t gridHeight, uint32_t tileWidth, uint32_t tileHeight, int32_t textureTileWidth, int32_t textureTileHeight, uint32_t chunkWidth = 32, uint32_t chunkHeight = 32)
     *  @brief Construct a TileMap.
     *
     *  Assert/undefined behavior when any of the input values are zero or below.
     *  @param gridWidth Amount of tiles on the X axis.
     *  @param gridHeight Amount of tiles on the Y axis.
     *  @param tileWidth Width of a single tile displayed on the screen in pixels with no scaling.
     *  @param tileHeight Height of a single tile displayed on the screen in pixels with no scaling.
     *  @param textureTileWidth Width of a tile in the texture image. Measured in pixels.
     *  @param textureTileHeight Height of a tile in the texture image. Measured in pixels.
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
     *  @fn void TileMap::translate(const glm::vec2& amount)
     *  @brief Move the TileMap using a vector.
     *  @param amount Vector containing the amount to move.
     ***
     *  @fn void TileMap::setOrigin(const glm::vec2& position)
     *  @brief Set the origin point of the TileMap, using a vector.
     *  
     *  The origin serves as the center point. This is where the object will be centered and all rotation and scaling will happen around this point. Also, if the position is set, the origin will be equivalent to that position. 
     *  @param position Position to set the origin to.
     ***
     *  @fn const glm::vec2& TileMap::getOrigin() const
     *  @brief Get the origin point of the TileMap.
     *  @return Vector containing the origin.
     ***
     *  @fn void TileMap::setRotation(const float amount)
     *  @brief Set the rotation.
     *  @param rotation Rotation angle in radians.
     ***
     *  @fn float TileMap::getRotation() const
     *  @brief Get the current rotation.
     *  @return The rotation.
     ***
     *  @fn void TileMap::rotate(const float amount)
     *  @brief Rotate the TileMap a specific amount.
     *  @param amount Amount in radians to rotate the TileMap.
     ***
     *  @fn void TileMap::setScale(const glm::vec2& scale)
     *  @brief Set the scale factor using a vector.
     *  @param scale Vector containing the scale factor.
     ***
     *  @fn const glm::vec2& TileMap::getScale() const
     *  @brief Get the current scale.
     *  @return Vector containing the scale.
     ***
     *  @fn void TileMap::scale(const glm::vec2& amount)
     *  @brief Scale the TileMap using a vector.
     *  @param amount Scale factor.
     ***
     *  @fn void TileMap::setParallax(const glm::vec2& parallax)
     *  @brief Set the parallax factor for each x and y axis separately.
     *  
     *  The factor determines how much the drawable moves relative to the camera. 
     *  A value of 1.0f is neutral, 0.5f is twice as slowly and 2.0f is twice as fast.
     *  @param parallax Parallax factor.
     ***
     *  @fn glm::vec2 TileMap::getParallax() const
     *  @brief Get the parallax factors as a vector.
     *  @return Parallax factor.
     ***
     *  @fn void TileMap::setOpacity(float opacity)
     *  @brief Set the opacity.
     *
     *  Assert/undefined behavior if the values is not within the range of [0.0f,1.0f].
     *  @param opacity Opacity.
     ***
     *  @fn float TileMap::getOpacity() const
     *  @brief Get the opacity.
     *  @return Opacity.
     ***
     *  @fn Color TileMap::getColor() const
     *  @brief Get the color.
     *  @return The color of the drawable.
     ***
     *  @fn void TileMap::setColor(const Color& color)
     *  @brief Set the color.
     *  @param color Color to set to.
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
     *  @fn const Texture& TileMap::getTexture() const
     *  @brief Get the current texture.
     *  @return Texture.
     ***
     *  @fn void TileMap::addTileDefinition(TileId id, const TileDefinition& tileDef)
     *  @brief Add a new tile definition.
     *  
     *  Before a tile is set, its type has to be registered with the TileMap using this function. It can then be accessed through the given id.
     *  @param id Id of the tile to add.
     *  @param tileDef Tile definition.
     ***
     *  @fn void TileMap::setTile(const glm::uvec2& position, TileId id, int32_t orientation = NORMAL)
     *  @brief Set a tile at the given coordinate.
     *
     *  The tile can optionally be given a bitmask representing an orientation. In other words, several values can be provided using the | operator. Only one rotation can be given at a time. The possible orientation values are: V_FLIP, H_FLIP, ROT_90, ROT_180, ROT_270 and PRESERVE. V_FLIP and H_FLIP represent vertical and horizontal flipping of the tile respectively and the ROT_* values describe rotation to varios degrees. The PRESERVE flag preserves any previous orientation and must not be given along with other flags.
     *
     *  Assert/undefined behavior when coordinates are outside the range of the tilemap, if tile name doesn't exist, or if the PRESERVE flag is passed with other values.
     *  @param position Coordinate of the tile to set,
     *  @param id Id of the tile definition to change it to.
     *  @param orientation Orientation of the tile.
     ***
     *  @fn void TileMap::unsetTile(const glm::uvec2& pos)
     *  @brief Set a tile to be transparent.
     *  
     *  This is the default state of tiles.
     *  Assert/undefined behavior when coordinates are outside the range of the tilemap.
     *  @param pos Coordinate of the tile to unset.
     ***
     *  @fn void TileMap::fill(TileId id)
     *  @brief Fill the whole tile map with a single tile type.
     *
     *  Assert/undefined behavior when tile type doesn't exist.
     *  @param id Id of the tile to fill with.
     ***
     *  @fn void TileMap::setTileColor(const glm::uvec2& pos, const fea::Color& color)
     *  @brief Set the color shade of a tile.
     *
     *  Assert/undefined behavior when tile is out of bounds.
     *  @param pos Location of the tile to colorize.
     *  @param color Color.
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
