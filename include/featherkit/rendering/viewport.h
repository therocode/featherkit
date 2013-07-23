#pragma once
#include <featherkit/rendering/camera.h>
#include <stdint.h>

namespace fea
{
    class Viewport
    {
        public:
            Viewport();
            Viewport(uint32_t w, uint32_t h);
            Viewport(uint32_t w, uint32_t h, const Camera& cam);
            void setSize(const glm::uvec2& s);
            const glm::uvec2& getSize() const;
            void setCamera(const Camera& cam);
            Camera& getCamera();
            glm::vec2 transformPoint(const glm::vec2 point) const;
            glm::vec2 untransformPoint(const glm::vec2 point) const;
        private:
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
     *  @fn Viewport::Viewport
     *  @brief Construct a Viewport.
     *  
     *  The default constructor constructs a Viewport with no translation and the viewing rectangle set to a width of 1.0f and a size of 1.0f.
     ***
     *  @fn Viewport::Viewport(uint32_t w, uint32_t h) : size(glm::uvec2(w, h))
     *  @brief Construct a Viewport with the given size.
     *
     *  @param w width of the new Viewport.
     *  @param h height of the new Viewport.
     ***
     *  @fn Viewport::Viewport(uint32_t w, uint32_t h, const Camera& cam) : size(glm::uvec2(w, h)), camera(cam)
     *  @brief Construct a Viewport with the given size and Camera.
     *
     *  @param w width of the new Viewport.
     *  @param h height of the new Viewport.
     *  @param cam Camera the new Viewport should use.
     ***
     *  @fn void Viewport::setSize(const glm::uvec2& s)
     *  @brief Set the size of the Viewport.
     *  @param s Size to set it to.
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
     *  @fn glm::vec2 Viewport::transformPoint(const glm::vec2 point) const
     *  @brief Transform a point to the Viewport.
     *
     *  The point given will be transformed into the coordinate space of the Viewport. For instance, it can be used to calculate where on the screen a certain object will be rendered if this Viewport is used.
     *  @param point World space coordinate to transform.
     *  @return The given point in the space of this Viewport.
     ***
     *  @fn glm::vec2 Viewport::untransformPoint(const glm::vec2 point) const
     *  @brief Transform a point from the Viewport back to world coordinates.
     *
     *  Does a reverse Viewport transformation of the given point. The point is given in screen space, and the return value will represent the given point in world coordinates. For example, this can be used to decide where in the world coordinates a given screen point is.
     *  @param point Screen space coordinate to reverse transform.
     *  @return The given point in world space.
     ***/
}
