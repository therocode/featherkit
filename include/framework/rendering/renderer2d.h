#pragma once
#include <framework/rendering/renderer2dbackend.h>
#include <framework/rendering/viewport.h>
#include <stdexcept>

namespace windbreeze
{
    class Drawable2D;

    class InvalidFontException : public std::runtime_error 
    {
        public:
            InvalidFontException(const std::string& message) 
                : std::runtime_error(message) { };
    };

    class Renderer2D
    {
        public:
            Renderer2D(Renderer2DBackend& b, Viewport v);
            void setup();
            void destroy();
            void clear();
            void preRender();
            void render(const Drawable2D& drawable);
            void postRender();
            void setViewport(const Viewport& viewport);
            Viewport& getViewport();
            void resize(uint32_t w, uint32_t h);
            int32_t addFont(uint8_t* fontData);
        private:
            Renderer2DBackend& backend;
            Viewport currentViewport;
            uint32_t clock = 0;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Renderer2D
     *@}
     ***
     *  @class Renderer2D
     *  @brief Represents a single game entity.
     *
     *  A game entity is no more than a collection of attributes, associated with the same entity ID. An attribute is a named value of any type. An example of an attribute would be an int named "health points" storing the value 23. An entity may have an arbitrary amount of attributes and every entity has a unique entity ID. 
     *
     *  Although usage may vary and is not restricted, the entities are meant to be used for ingame objects that need to store data. These could include the player, enemies, pickups, bullets, and so on.
     ***
     *  @fn Entity::Entity(EntityId i, EntityManager& m)
     *  @brief Construct an Entity. 
     *
     *  This sets the EntityId to the supplied ID. The entity stores the EntityManager reference internally for using when getting and setting attributes.
     *
     *  Observe that entities aren't mean to be created manually, but using the EntityManager::CreateEntity function.
     *  @param i ID of the new entity.
     *  @param m EntityManager that the entity will use.
     ***/
}
