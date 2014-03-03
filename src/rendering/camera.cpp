#include <featherkit/rendering/camera.hpp>

namespace fea
{
    Camera::Camera() : mPosition(glm::vec2(0.0f, 0.0f)), mZoom(glm::vec2(1.0f, 1.0f)), mRotation(0.0f)
    {
    }

    Camera::Camera(glm::vec2 p, glm::vec2 z) : mPosition(p), mZoom(z), mRotation(0.0f)
    {
    }

    void Camera::setPosition(glm::vec2 p)
    {
        mPosition = p;
    }
    
    const glm::vec2& Camera::getPosition() const
    {
        return mPosition;
    }
            
    void Camera::translate(glm::vec2 p)
    {
        mPosition += p;
    }
    
    void Camera::setZoom(glm::vec2 z)
    {
        mZoom = z;
    }
    
    const glm::vec2& Camera::getZoom() const
    {
        return mZoom;
    }

    void Camera::setRotation(float radians)
    {
        mRotation = radians;
    }

    float Camera::getRotation() const
    {
        return mRotation;
    }
    
    void Camera::rotate(float radians)
    {
        mRotation += radians;
    }

        glm::mat2x2 Camera::getRotationMatrix() const
    {
        glm::mat2x2 result;

        float sin = glm::sin(mRotation);
        float cos = glm::cos(mRotation);

        glm::mat2x2 rot = glm::mat2x2(cos, sin, -sin, cos);

        return result * rot;
    }
}
