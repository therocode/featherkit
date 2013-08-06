#include <featherkit/rendering/drawable2d.h>

namespace fea
{
    Drawable2D::Drawable2D() : isText(false), rotation(0.0f), scaling(glm::vec2(1.0f, 1.0f)), parallax(1.0f), colour(1.0f, 1.0f, 1.0f), opacity(1.0f)
    {
    }

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
    
    float Drawable2D::getParallax() const
    {
        return parallax;
    }
        
    void Drawable2D::setColour(float r, float g, float b)
    {
        colour = glm::vec3(r, g, b);
    }
    
    void Drawable2D::setColour(const glm::vec3& c)
    {
        colour = c;
    }
    
    glm::vec3 Drawable2D::getColour() const
    {
        return colour;
    }
    
    void Drawable2D::setOpacity(float o)
    {
        opacity = o;
    }

    float Drawable2D::getOpacity() const
    {
        return opacity;
    }
    
    void Drawable2D::addTransformation(const glm::mat2x2& t)
    {
        transformations.push_back(t);
    }

    const glm::mat2x2& Drawable2D::getTransformation(uint32_t index) const
    {
        return transformations[index];
    }

    uint32_t Drawable2D::getTransformationCount() const
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
        renderData.colour = colour;
        renderData.opacity = opacity;
    }
    
    AABB Drawable2D::getAABB() const
    {
        AABB result;
        std::vector<float> transformed = getVerticesTransformed();
        result.start.x = transformed[0];
        result.start.y = transformed[1];
        result.end.x = transformed[0];
        result.end.y = transformed[1];

        for(uint32_t i = 0; i < transformed.size(); i+=2)
        {
            if(transformed[i] < result.start.x)
                result.start.x = transformed[i];
            if(transformed[i+1] < result.start.y)
                result.start.y = transformed[i+1];
            if(transformed[i] > result.end.x)
                result.end.x = transformed[i];
            if(transformed[i+1] > result.end.y)
                result.end.y = transformed[i+1];
        }

        return result;
    }
}
