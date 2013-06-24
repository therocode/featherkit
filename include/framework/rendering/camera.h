#pragma once
#include <framework/glm/glm.hpp>

namespace windbreeze
{
    class Camera
    {
        public:
            Camera() : position(glm::vec2(0.0f, 0.0f)), zoom(glm::vec2(1.0f, 1.0f)) {}
            Camera(float x, float y, float xZoom = 1.0f, float yZoom = 1.0f) : position(glm::vec2(x, y)), zoom(glm::vec2(xZoom, yZoom)) {}
            Camera(glm::vec2 p, glm::vec2 z = glm::vec2(1.0f, 1.0f)) : position(p), zoom(z) {}
            void setPosition(float x, float y);
            void setPosition(glm::vec2 p);
            const glm::vec2& getPosition();
            void translate(float x, float y);
            void translate(glm::vec2 p);
            void setZoom(float x, float y);
            void setZoom(glm::vec2 z);
            const glm::vec2& getZoom();
            void setRotation(float radians);
            float getRotation();
            void rotate(float radians);
            glm::mat2x2 getTransformation();
        private:
            glm::vec2 position;
            glm::vec2 zoom;
            float rotation = 0.0f;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Camera
     *@}
     ***
     *  @class Camera
     *  @brief Represents a way to look at the world.
     *
     *  The Camera class contains three modificators. Position, zoom and rotation. Position is the centre point of the Camera, Zoom is how big things appear to the Camera, and rotation is the orientation of the Camera. 
     ***
     *  @fn Camera::Camera()
     *  @brief Construct a camera.
     *
     *  The constructed Camera will have a position of 0.0f, 0.0f, and neutral zoom and rotation.
     ***
     *  @fn Camera::Camera(float x, float y)
     *  @brief Construct a Camera with the given position.
     *
     *  The zoom and rotation of the Camera will be neutral.
     *  @param x X position.
     *  @param y Y position.
     ***
     *  @fn Camera::Camera(float x, float y, float xZoom, float yZoom)
     *  @brief Construct a Camera with the given position and zoom.
     *
     *  The rotation of the Camera will be neutral.
     *  @param x X position.
     *  @param y Y position.
     *  @param xZoom X zoom.
     *  @param yZoom Y zoom.
     ***/
}
