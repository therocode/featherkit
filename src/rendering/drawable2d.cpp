#include <framework/rendering/drawable2d.h>
#include <stdint.h>

namespace windbreeze
{
    const std::vector<float>& Drawable2D::getVertices() const
    {
        return vertices;
    }
    
    std::vector<float> Drawable2D::getVerticesTransformed() const
    {
        std::vector<float> result;

        glm::vec2 point;

        float sin = glm::sin(rotation);
        float cos = glm::cos(rotation);
        glm::mat2x2 rot = glm::mat2x2(cos, sin, -sin, cos);

        for(uint32_t i = 0; i < vertices.size(); i+=2)
        {
            point = glm::vec2(vertices[i], vertices[i+1]);
            point = ((rot * transformation) * point) + position;
            result.push_back(point.x);
            result.push_back(point.y);
        }
        
        return result;
    }
    
    void Drawable2D::setPosition(const float x, const float y)
    {
        position.x = x;
        position.y = y;
    }
    
    void Drawable2D::setPosition(const glm::vec2& p)
    {
        position = p;
    }
    
    const glm::vec2& Drawable2D::getPosition() const
    {
        return position;
    }

    void Drawable2D::translate(const float x, const float y)
    {
        position += glm::vec2(x, y);
    }
    
    void Drawable2D::translate(const glm::vec2& p)
    {
        position += p;
    }

    void Drawable2D::setRotation(const float radians)
    {
        rotation = radians;
    }
    
    float Drawable2D::getRotation()
    {
        return rotation;
    }

    void Drawable2D::rotate(const float radians)
    {
        rotation += radians;
    }
}
