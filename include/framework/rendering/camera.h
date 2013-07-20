#pragma once
#include <framework/glm/glm.hpp>

namespace fk
{
    class Camera
    {
        public:
            Camera();
            Camera(float x, float y, float xZoom = 1.0f, float yZoom = 1.0f);
            Camera(glm::vec2 p, glm::vec2 z = glm::vec2(1.0f, 1.0f));
            void setPosition(float x, float y);
            void setPosition(glm::vec2 p);
            const glm::vec2& getPosition() const;
            void translate(float x, float y);
            void translate(glm::vec2 p);
            void setZoom(float x, float y);
            void setZoom(glm::vec2 z);
            const glm::vec2& getZoom() const;
            void setRotation(float radians);
            float getRotation() const;
            void rotate(float radians);
            glm::mat2x2 getRotationMatrix() const;
        private:
            glm::vec2 position;
            glm::vec2 zoom;
            float rotation;
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
     *  @fn Camera::Camera(float x, float y, float xZoom = 1.0f, float yZoom = 1.0f)
     *  @brief Construct a Camera with the given position and zoom.
     *
     *  The rotation of the Camera will be neutral.
     *  @param x X position.
     *  @param y Y position.
     *  @param xZoom X zoom, default 1.0f.
     *  @param yZoom Y zoom, default 1.0f.
     ***
     *  @fn Camera::Camera(glm::vec2 p, glm::vec2 z = glm::vec2(1.0f, 1.0f))
     *  @brief Construct a Camera with the given position and zoom, given as vectors.
     *
     *  The rotation of the Camera will be neutral.
     *  @param p Vector containing the position.
     *  @param z Vector containing the zoom, default is 1.0f, 1.0f.
     ***
     *  @fn void Camera::setPosition(float x, float y)
     *  @brief Set the position of the Camera.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     ***
     *  @fn void Camera::setPosition(glm::vec2 p)
     *  @brief Set the position of the Camera using a vector.
     *  @param p Vector with the new position.
     ***
     *  @fn const glm::vec2& Camera::getPosition() const
     *  @brief Get the position of the Camera.
     *  @return Camera position.
     ***
     *  @fn void Camera::translate(float x, float y)
     *  @brief Move the Camera a given amount of units.
     *  @param x Amount to move on the X axis.
     *  @param y Amount to move on the Y axis.
     ***
     *  @fn void Camera::translate(glm::vec2 p)
     *  @brief Move the Camera an amount of units given as a vector.
     *  @param p Amount to move the Camera.
     ***
     *  @fn void Camera::setZoom(float x, float y)
     *  @brief Set the zoom factor of the Camera.
     *  @param x Factor along the X axis.
     *  @param y Factor along the Y axis.
     ***
     *  @fn void Camera::setZoom(glm::vec2 z)
     *  @brief Set the zoom factor of the Camera given as a vector.
     *  @param z Zoom factor to set.
     ***
     *  @fn const glm::vec2& Camera::getZoom() const
     *  @brief Get the zoom factor of the Camera.
     *  @return Vector with the zoom factor.
     ***
     *  @fn void Camera::setRotation(float radians)
     *  @brief Set the rotation angle of the Camera.
     *  @param radians Degrees in radians to set it to.
     ***
     *  @fn float Camera::getRotation() const
     *  @brief Get the rotation angle of the Camera.
     *  @return The angle of the Camera in radians.
     ***
     *  @fn void Camera::rotate(float radians)
     *  @brief Rotate the camera with a given angle.
     *  @param radians Amount of dregrees in radians to turn the Camera.
     ***
     *  @fn glm::mat2x2 Camera::getRotationMatrix() const
     *  @brief Get the rotation matrix of the Camera.
     *  @return Matrix representing the rotation of the Camera.
     ***/
}
