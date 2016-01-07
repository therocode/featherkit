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
        public:
            struct Tile
            {
                TileId id;
                fea::Color color;
                int32_t ticksUntilChange;
            };

        private:
            struct TileChunk
            {
                TileChunk(int32_t chunkSize);
                void setTile(const glm::ivec2& position, TileId id);
                void setTileColor(const glm::ivec2& position, const fea::Color& color);
                void unsetTile(const glm::ivec2& position);
                const Tile& getTile(const glm::ivec2& position) const;
                Tile& getTile(const glm::ivec2& position);
                int32_t mChunkSize;
                int32_t tileCount;
                std::vector<Tile> tiles;
                std::vector<bool> tilesSet;
            };

            struct CacheEntry
            {
                std::vector<float> vertices;
                std::vector<float> texCoords;
                std::vector<float> colors;
            };

        public:
            TileMap(const glm::ivec2& tileSize, const glm::ivec2& tileTextureSize, int32_t chunkSize = 32);
            void setTexture(const Texture& texture);
            const Texture& getTexture() const;
            void addTileDefinition(TileId id, const TileDefinition& tileDef);
            void setTile(const glm::ivec2& pos, TileId id);
            void unsetTile(const glm::ivec2& pos);
            void fillRegion(const glm::ivec2& startCorner, const glm::ivec2& size, TileId id);
            void clear();
            void setTileColor(const glm::ivec2& pos, const fea::Color& color);
            const Tile* getTile(const glm::ivec2& pos) const;
            glm::ivec2 worldToTileCoordinates(const glm::vec2& coordinates) const;
            glm::vec2 tileToWorldCoordinates(const glm::ivec2& tile) const;
            const glm::ivec2& getTileSize() const;
            const glm::ivec2& getTileTextureSize() const;
            void tick();
            virtual void updateRenderInfo(std::vector<RenderEntity>& renderInfo, bool updateVertices, bool updateUniforms) const override;
            void setCullRegion(const glm::vec2& start, const glm::vec2& end);
            void setCullEnabled(bool enabled);
        private:
            glm::ivec2 tileToChunk(const glm::ivec2& pos) const;
            glm::ivec2 tileToTileInChunk(const glm::ivec2& pos) const;
            RenderEntity renderInfoFromChunk(const glm::ivec2& chunkPos, const TileChunk& chunk) const;
            void setDirty(const glm::ivec2& chunk) const;
            bool isDirty(const glm::ivec2& chunk) const;
            TileChunk& getOrCreateChunk(const glm::ivec2& coordinate);
            glm::ivec2 mTileSize;
            glm::ivec2 mTileTextureSize;
            const Texture* mTexture;

            std::unordered_map<TileId, TileDefinition> mTileDefinitions;
            std::unordered_map<glm::ivec2, TileChunk> mChunks;
            std::unordered_map<glm::ivec2, Tile*> mAnimatedTiles;

            mutable std::unordered_map<glm::ivec2, CacheEntry> mChunkCache;

            glm::vec2 mCullStart;
            glm::vec2 mCullEnd;
            bool mCullEnabled;

            int32_t mChunkSize;
    };
    /** @addtogroup Render2D
     *@{
     *  @struct TileDefinition
     *  @struct Tile
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
     *  @fn TileDefinition::TileDefinition(const glm::ivec2& texPos, TileId next = "", uint32_t ticks = 0)
     *  @brief Construct a TileDefinition.
     *  @param texPos Coordinates of the subrectangle to use as texture.
     *  @param next TileDefinition to change to. Only needed if the tile is animated.
     *  @param ticks Amount of ticks until the tile is changed. Only needed if the tile is animated.
     ***
     *  @var TileDefinition::tileTexPosition
     *  @brief Coordinates describing the position of the subrect of the texture to use for this tile. For example if the map tile in the upper left corner is to be used, this variable should be (0,0). If the tile next to it is to be used, it should be (1,0).
     ***
     *  @var TileDefinition::nextTile
     *  @brief If the tile is meant to be animated, this should be set to the name of the tile to switch to.
     ***
     *  @var TileDefinition::ticksUntilChange
     *  @brief The amount of ticks to display this tile before it is changed to the one defined using TileDefinition::mNextTile.
     ***
     *  @class TileMap
     *  @brief Represents a graphical tilemap with tiles that can be set freely and animated. It is a drawable which can be passed to the renderer.
     *  
     *  The tilemap is borderless which means that you don't have to decide how many tiles it fits. Instead tiles can just be set freely and the rest is internally managed.
     ***
     *  @struct Tile
     *  @brief Data container describing a tile.
     *  
     *  The data contained describes the type (id) of the tile, the color the tile has been set to, and the amount of ticks until the tile changes, if it is an animation tile.
     ***
     *  @var Tile::id
     *  @brief The type of the tile, as described by the TileDefinitions given to the tilemap.
     ***
     *  @var Tile::color
     *  @brief The color that the tile has been set to using setTileColor. Default is fea::Color::White.
     ***
     *  @var Tile::ticksUntilChange
     *  @brief The amount of ticks (as given by the tick function) until the tile changes to another tile as a part of the tile animation process.
     ***
     *  @fn TileMap::TileMap(const glm::ivec2& tileSize, const glm::ivec2& tileTextureSize, int32_t chunkSize = 32);
     *  @brief Construct a TileMap.
     *
     *  Assert/undefined behavior when any of the input values are zero or below.
     *  @param tileSize Size of a single tile displayed on the screen in pixels.
     *  @param chunkSize Size of the internal chunks that the tilemap is divided into. 
     *  @param tileTextureSize Size of a tile in the texture image.
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
     *  Before a tile is set, its type has to be registered with the TileMap using this function. It can then be set using the given id.
     *  @param id Id of the tile to add.
     *  @param tileDef Tile definition.
     ***
     *  @fn void TileMap::setTile(const glm::ivec2& position, TileId id)
     *  @brief Set a tile to a specific type at the given coordinate.
     *
     *  Assert/undefined behavior if the tile id doesn't exist.
     *  @param position Coordinate of the tile to set,
     *  @param id Id of the tile definition to change it to.
     ***
     *  @fn void TileMap::unsetTile(const glm::ivec2& pos)
     *  @brief Remove a tile at a certain position.
     *  
     *  This is the default state of tiles, so unsetting tiles is equivalent to adding "holes" in the tilemap.
     *  @param pos Coordinate of the tile to unset.
     ***
     *  @fn void TileMap::fillRegion(const glm::ivec2& startCorner, const glm::ivec2& size, TileId id)
     *  @brief Fill a rectangular region of the tile map with a single tile type.
     *
     *  Assert/undefined behavior when tile type doesn't exist.
     *  @param startCorner Upper left corner of region.
     *  @param size Region size in tiles.
     *  @param id Id of the tile to fill with.
     ***
     *  @fn void TileMap::setTileColor(const glm::ivec2& pos, const fea::Color& color)
     *  @brief Set the color shade of a tile.
     *
     *  @param pos Location of the tile to colorize.
     *  @param color Color.
     ***
     *  @fn void TileMap::clear();
     *  @brief Clear the tile map of all tiles.
     ***
     *  @fn const Tile* TileMap::getTile(const glm::ivec2& pos) const);
     *  @brief Retreive a tile from the tilemap
     *  
     *  @param pos Location of the tile to retreive
     *  @return A pointer to an instance of the Tile struct which provides information on the tile. nullptr in case no tile exists at the given location.
     ***
     *  @fn glm::ivec2 TileMap::worldToTileCoordinates(const glm::vec2& coordinates) const
     *  @brief Get the tile coordinates for the given world coordinate on the TileMap.
     *
     *  Takes tilemap rotation/scale/position into account.
     *  @param coordinates Coordinate to convert.
     *  @return Tile coordinates.
     ***
     *  @fn glm::vec2 TileMap::tileToWorldCoordinates(const glm::ivec2& coordinates) const
     *  @brief Get the world coordinates for the given tile coordinate on the TileMap.
     *
     *  Takes tilemap rotation/scale/position into account.
     *  @param coordinates Coordinate to convert.
     *  @return World coordinates.
     ***
     *  @fn const glm::ivec2& TileMap::getTileSize() const
     *  @brief Get the size of a single tile.
     *  @return The tile size.
     ***
     *  @fn const glm::ivec2& TileMap::getTileTextureSize() const
     *  @brief Get the size of a tilee in the tile texture.
     *  @return The tile texture size.
     ***
     *  @fn void TileMap::tick()
     *  @brief Advance the animation clock by one step.
     *  
     *  This function needs to be called once every frame for the animations to work properly
     ***
     *  @fn void TileMap::setCullRegion(const glm::vec2& start, const glm::vec2& end)
     *  @brief Set the region that defines the area of the tilemap that should be visible.
     *
     *  The cull region is defined by an axis aligned rectangle that is used to ensure that an area is visible when culling is enabled. There is no guarantee that tiles outside of the culling region will be visible. This option only has an effect when culling is enabled using setCullEnabled.
     *  @param start Top-left corner of the region.
     *  @param start Bottom-right corner of the region.
     ***
     *  @fn void TileMap::setCullEnabled(bool enabled);
     *  @brief Enable or disable culling.
     *
     *  Culling is a way of optimizing rendering by not rendering things that are not visible. This culling feature has a region specified by setCullRegion and the tilemap will try its best to not render tile areas outside of this given region. 
     *  @param enabled True if enabled.
     ***/
}
