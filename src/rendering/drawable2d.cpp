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

        for(uint32_t i = 0; i < vertices.size(); i+=2)
        {
            glm::vec2 point(vertices[i], vertices[i+1]);
            point = transformation * point + position;
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
}
