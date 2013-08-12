#pragma once
#include <featherkit/rendering/camera.h>
#include <stdint.h>

namespace fea
{
    class Viewport
    {
        public:
            Viewport();
            Viewport(uint32_t w, uint32_t h, int32_t x = 0, int32_t y = 0, const Camera& cam = Camera());
            Viewport(const glm::uvec2& s, const glm::ivec2& pos = glm::ivec2(), const Camera& cam = Camera());
            const glm::ivec2& getPosition() const;
            const glm::uvec2& getSize() const;
            void setCamera(const Camera& cam);
            Camera& getCamera();
            glm::vec2 transformPoint(float x, float y) const;
            glm::vec2 transformPoint(const glm::vec2 point) const;
            glm::vec2 untransformPoint(float x, float y) const;
            glm::vec2 untransformPoint(const glm::vec2 point) const;
        private:
            glm::ivec2 position;
            glm::uvec2 size;
            Camera camera;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Viewport
     *@}
     ***
     *  @class Viewport
     *  @brief Represents a way of viewing a scene.
     *
     *  The scene is defined by a viewing rectangle which contains the size of the view, and a Camera which contains its rotation and zoom.
     ***
     *  @fn Viewport::Viewport()
     *  @brief Construct a Viewport.
     *  
     *  The default constructor constructs a Viewport with no translation and the viewing rectangle set to a width of 1.0f and a size of 1.0f.
     ***
     *  @fn Viewport::Viewport(uint32_t w, uint32_t h, int32_t x = 0, int32_t y = 0, const Camera& cam = Camera())
     *  @brief Construct a Viewport with the given size, position and camera.
     *
     *  @param w width of the new Viewport.
     *  @param h height of the new Viewport.
     *  @param x X position of the top-left corner. Default is 0.
     *  @param y Y position of the top-left corner. Default is 0.
     *  @param cam Camera to use.
     ***
     *  @fn Viewport::Viewport(const glm::uvec2& s, const glm::ivec2& pos = glm::ivec2(), const Camera& cam = Camera())
     *  @brief Construct a Viewport with the given size, position and camera.
     *
     *  @param s Size of the new Viewport.
     *  @param pos Position of the top-left corner. Default is 0,0.
     *  @param cam Camera to use.
     ***
     *  @fn const glm::ivec2& Viewport::getPosition() const
     *  @brief Get the position of the top-left corner.
     *  @return Vector containing position.
     ***
     *  @fn const glm::uvec2& Viewport::getSize() const
     *  @brief Get the size of the Viewport.
     *  @return Vector containing the current size.
     ***
     *  @fn void Viewport::setCamera(const Camera& cam)
     *  @brief Set the Camera of the Viewport.
     *  @param cam Camera to set it to.
     ***
     *  @fn Camera& Viewport::getCamera()
     *  @brief Get the Camera currently in use by the Viewport. The camera might be modified external.
     *  @return The current camera.
     ***
     *  @fn glm::vec2 Viewport::transformPoint(float x, float y) const
     *  @brief Transform a point to the Viewport.
     *
     *  The point given will be transformed into the coordinate space of the Viewport. For instance, it can be used to calculate where on the screen a certain object will be rendered if this Viewport is used.
     *  @param x World space X coordinate to transform.
     *  @param y World space Y coordinate to transform.
     *  @return The given point in the space of this Viewport.
     ***
     *  @fn glm::vec2 Viewport::transformPoint(const glm::vec2 point) const
     *  @brief Transform a point to the Viewport.
     *
     *  The point given will be transformed into the coordinate space of the Viewport. For instance, it can be used to calculate where on the screen a certain object will be rendered if this Viewport is used.
     *  @param point World space coordinate to transform.
     *  @return The given point in the space of this Viewport.
     ***
     *  @fn glm::vec2 Viewport::untransformPoint(float x, float y) const
     *  @brief Transform a point from the Viewport back to world coordinates.
     *
     *  Does a reverse Viewport transformation of the given point. The point is given in screen space, and the return value will represent the given point in world coordinates. For example, this can be used to decide where in the world coordinates a given screen point is.
     *  @param x Screen space X coordinate to reverse transform.
     *  @param y Screen space Y coordinate to reverse transform.
     *  @return The given point in world space.
     ***
     *  @fn glm::vec2 Viewport::untransformPoint(const glm::vec2 point) const
     *  @brief Transform a point from the Viewport back to world coordinates.
     *
     *  Does a reverse Viewport transformation of the given point. The point is given in screen space, and the return value will represent the given point in world coordinates. For example, this can be used to decide where in the world coordinates a given screen point is.
     *  @param point Screen space coordinate to reverse transform.
     *  @return The given point in world space.
     ***/
}
