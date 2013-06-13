#include <framework/rendering/camera.h>

namespace windbreeze
{
    Camera::Camera(float x, float y, float width, float height)
    {
        position =  glm::vec2(x, y);
        size = glm::vec2(width, height);
    }

    Camera::Camera(glm::vec2 p, glm::vec2 s)
    {
        position = p;
        size = s;
    }

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
    
    void Camera::setSize(float x, float y)
    {
        size = glm::vec2(x, y);
    }

    void Camera::setSize(glm::vec2 s)
    {
        size = s;
    }
    
    const glm::vec2& Camera::getSize()
    {
        return size;
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
    
    glm::vec2 Camera::transformPoint(const glm::vec2 point)
    {
        glm::vec2 halfCameraSize = size * 0.5f;
        return glm::inverse(getTransformation()) * (point + (-position) - halfCameraSize) + halfCameraSize; 
    }
}
