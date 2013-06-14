#include <framework/rendering/camera.h>

namespace windbreeze
{
    void Camera::setPosition(float x, float y)
    {
        position = glm::vec2(x, y);
    }

    void Camera::setPosition(glm::vec2 p)
    {
        position = p;
    }
    
    const glm::vec2& Camera::getPosition()
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
    
    const glm::vec2& Camera::getZoom()
    {
        return zoom;
    }

    void Camera::setRotation(float radians)
    {
        rotation = radians;
    }
    
    void Camera::rotate(float radians)
    {
        rotation += radians;
    }

    glm::mat2x2 Camera::getTransformation()
    {
        glm::mat2x2 result;

        float sin = glm::sin(rotation);
        float cos = glm::cos(rotation);

        glm::mat2x2 rotation = glm::mat2x2(cos, sin, -sin, cos);

        return result * rotation;
    }
}
