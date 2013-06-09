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

    void Camera::setRotation(float radians)
    {
        rotation = radians;
    }

    glm::vec2 Camera::getTranslation()
    {
        return -position;
    }

    glm::mat2x2 Camera::getTransformation()
    {
        glm::mat2x2 result;

        float sin = glm::sin(rotation);
        float cos = glm::cos(rotation);

        glm::mat2x2 rotation = glm::mat2x2(cos, sin, -sin, cos);

        return glm::inverse(result * rotation);
    }
}
