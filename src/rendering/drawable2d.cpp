#include <framework/rendering/drawable2d.h>

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

        glm::mat2x2 transformation;

        for(uint32_t i = 0; i < transformations.size(); i++)
        {
            transformation *= transformations[i];
        }

        for(uint32_t i = 0; i < vertices.size(); i+=2)
        {
            point = glm::vec2(vertices[i], vertices[i+1]);
            point = (rot * ( transformation * (scaling * point) - origin)) + position;
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
    
    void Drawable2D::setOrigin(const float x, const float y)
    {
        origin = glm::vec2(x, y);
    }

    void Drawable2D::setOrigin(const glm::vec2& p)
    {
        origin = p;
    }

    const glm::vec2& Drawable2D::getOrigin() const
    {
        return origin;
    }

    void Drawable2D::setRotation(const float radians)
    {
        rotation = radians;
    }
    
    float Drawable2D::getRotation() const
    {
        return rotation;
    }

    void Drawable2D::rotate(const float radians)
    {
        rotation += radians;
    }

    void Drawable2D::setScale(const float x, const float y)
    {
        scaling = glm::vec2(x, y);
    }

    void Drawable2D::setScale(const glm::vec2& s)
    {
        scaling = s;
    }

    const glm::vec2& Drawable2D::getScale() const
    {
        return scaling;
    }

    void Drawable2D::scale(const float x, const float y)
    {
        scaling *= glm::vec2(x, y);
    }

    void Drawable2D::scale(const glm::vec2& s)
    {
        scaling *= s;
    }
    
    void Drawable2D::setParallax(float p)
    {
        parallax = p;
    }
    
    float Drawable2D::getParallax()
    {
        return parallax;
    }
    
    void Drawable2D::addTransformation(const glm::mat2x2& t)
    {
        transformations.push_back(t);
    }

    glm::mat2x2& Drawable2D::getTransformation(uint32_t index)
    {
        return transformations[index];
    }

    uint32_t Drawable2D::getTransformationCount()
    {
        return transformations.size();
    }

    void Drawable2D::clearTransformations()
    {
        transformations.clear();
    }
    
    void Drawable2D::getRenderData(RenderData& renderData, uint32_t time) const
    {
        (void) time; //getting rid of unused parameter warning
        renderData.vertices = getVerticesTransformed();
        renderData.parallax = parallax;
    }
}
