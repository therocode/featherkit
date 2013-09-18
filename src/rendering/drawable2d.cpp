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

    void setDrawMode(GLenum mode)
    {
        drawMode = mode;
    }

    GLenum getDrawMode() const
    {
        return drawMode;
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

    RenderInfo Drawable2D::getRenderInfo() const
    {
        RenderInfo temp;
        std::hash<std::string> stringHasher;

        temp.drawMode = drawMode;
        temp.uniforms.push_back(Uniform(stringHasher("texture"), Uniform::TEXTURE, 0)); //fixi
        temp.uniforms.push_back(Uniform(stringHasher("constraints"), Uniform::VEC4, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); //fixi
        temp.uniforms.push_back(Uniform(stringHasher("parallax"), Uniform::FLOAT, parallax);
        temp.uniforms.push_back(Uniform(stringHasher("colour"), Uniform::VEC3, colour));
        temp.uniforms.push_back(Uniform(stringHasher("opacity"), Uniform::FLOAT, opacity);
        temp.uniforms.push_back(Uniform(stringHasher("origin"), Uniform::VEC2, origin);
        temp.uniforms.push_back(Uniform(stringHasher("rotation"), Uniform::FLOAT, rotation);
        temp.uniforms.push_back(Uniform(stringHasher("scaling"), Uniform::VEC2, scaling);

        temp.vertexAttributes.push_back(stringHasher("position"), vertices.size(), &vertices[0]);
        temp.vertexAttributes.push_back(stringHasher("texcoords"), 0, nullptr); //ajaj?
        return temp;
    }
}
