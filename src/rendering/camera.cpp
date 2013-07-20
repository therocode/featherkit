#include <featherkit/rendering/camera.h>

namespace fk
{
    Camera::Camera() : position(glm::vec2(0.0f, 0.0f)), zoom(glm::vec2(1.0f, 1.0f)), rotation(0.0f)
    {
    }

    Camera::Camera(float x, float y, float xZoom, float yZoom) : position(glm::vec2(x, y)), zoom(glm::vec2(xZoom, yZoom)), rotation(0.0f)
    {
    }

    Camera::Camera(glm::vec2 p, glm::vec2 z) : position(p), zoom(z), rotation(0.0f)
    {
    }

    void Camera::setPosition(float x, float y)
    {
        position = glm::vec2(x, y);
    }

    void Camera::setPosition(glm::vec2 p)
    {
        position = p;
    }
    
    const glm::vec2& Camera::getPosition() const
    {
        return position;
    }
            
    void Camera::translate(float x, float y)
    {
        position += glm::vec2(x, y);
    }
    
    void Camera::translate(glm::vec2 p)
    {
        position += p;
    }
    
    void Camera::setZoom(float x, float y)
    {
        zoom = glm::vec2(x, y);
    }

    void Camera::setZoom(glm::vec2 z)
    {
        zoom = z;
    }
    
    const glm::vec2& Camera::getZoom() const
    {
        return zoom;
    }

    void Camera::setRotation(float radians)
    {
        rotation = radians;
    }

    float Camera::getRotation() const
    {
        return rotation;
    }
    
    void Camera::rotate(float radians)
    {
        rotation += radians;
    }

        glm::mat2x2 Camera::getRotationMatrix() const
    {
        glm::mat2x2 result;

        float sin = glm::sin(rotation);
        float cos = glm::cos(rotation);

        glm::mat2x2 rotation = glm::mat2x2(cos, sin, -sin, cos);

        return result * rotation;
    }
}
