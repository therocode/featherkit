#pragma once
#include <fea/config.hpp>
#include <glm/glm.hpp>

namespace fea
{
    class FEA_API Camera
    {
        public:
            Camera();
            Camera(glm::vec2 position, glm::vec2 zoom = glm::vec2(1.0f, 1.0f));
            void setPosition(glm::vec2 position);
            const glm::vec2& getPosition() const;
            void translate(glm::vec2 position);
            void setZoom(glm::vec2 zoom);
            const glm::vec2& getZoom() const;
            void zoom(glm::vec2 zoom);
            void setRotation(float radians);
            float getRotation() const;
            void rotate(float radians);
            glm::mat2x2 getRotationMatrix() const;
            glm::vec2 transformPoint(const glm::vec2 point) const;
            glm::vec2 untransformPoint(const glm::vec2 point) const;
        private:
            glm::vec2 mPosition;
            glm::vec2 mZoom;
            float mRotation;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Camera
     *@}
     ***
     *  @class Camera
     *  @brief Represents a way to look at the world.
     *
     *  The Camera class contains three modificators. Position, zoom and rotation. Position is the center point of the Camera, Zoom is how big things appear to the Camera, and rotation is the orientation of the Camera. 
     ***
     *  @fn Camera::Camera()
     *  @brief Construct a camera.
     *
     *  The constructed Camera will have a position of 0.0f, 0.0f, and neutral zoom and rotation.
     ***
     *  @fn Camera::Camera(glm::vec2 position, glm::vec2 zoom = glm::vec2(1.0f, 1.0f))
     *  @brief Construct a Camera with the given position and zoom, given as vectors.
     *
     *  The rotation of the Camera will be neutral.
     *  @param position Vector containing the position.
     *  @param zoom Vector containing the zoom, default is 1.0f, 1.0f.
     ***
     *  @fn void Camera::setPosition(glm::vec2 position)
     *  @brief Set the position of the Camera using a vector.
     *  @param position Vector with the new position.
     ***
     *  @fn const glm::vec2& Camera::getPosition() const
     *  @brief Get the position of the Camera.
     *  @return Camera position.
     ***
     *  @fn void Camera::translate(glm::vec2 position)
     *  @brief Move the Camera an amount of units given as a vector.
     *  @param position Amount to move the Camera.
     ***
     *  @fn void Camera::setZoom(glm::vec2 zoom)
     *  @brief Set the zoom factor of the Camera given as a vector.
     *  @param zoom Zoom factor to set.
     ***
     *  @fn const glm::vec2& Camera::getZoom() const
     *  @brief Get the zoom factor of the Camera.
     *  @return Vector with the zoom factor.
     ***
     *  @fn void Camera::zoom(glm::vec2& zoom) const
     *  @brief Zoom the camera with the given amount.
     *  @param zoom Zoom factor.
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
     ***
     *  @fn glm::vec2 Camera::transformPoint(const glm::vec2 point) const
     *  @brief Transform a point to the Camera.
     *
     *  The point given will be transformed into the coordinate space of the Camera. For instance, it can be used to calculate where on the screen a certain object will be rendered if this Camera is used.
     *
     *  This does not take viewport boundaries into account. If that is desired, use Viewport::transformPoint instead.
     *
     *  @param point World space coordinate to transform.
     *  @return The given point in the space of this Camera.
     ***
     *  @fn glm::vec2 Camera::untransformPoint(const glm::vec2 point) const
     *  @brief Transform a point from the Camera back to world coordinates.
     *
     *  Does a reverse Camera transformation of the given point. The point is given in screen space, and the return value will represent the given point in world coordinates. For example, this can be used to decide where in the world coordinates a given screen point is.
     *
     *  This does not take viewport boundaries into account. If that is desired, use Viewport::transformPoint instead.
     *
     *  @param point Screen space coordinate to reverse transform.
     *  @return The given point in world space.
     ***/
}
