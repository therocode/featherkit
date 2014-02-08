#include <featherkit/rendering/drawable2d.h>

namespace fea
{
    Drawable2D::Drawable2D() : mDrawMode(0), mRotation(0.0f), mScaling(glm::vec2(1.0f, 1.0f)), mParallax(1.0f), mColour(1.0f, 1.0f, 1.0f, 1.0f)
    {
    }

    const std::vector<float>& Drawable2D::getVertices() const
    {
        return mVertices;
    }
    
    void Drawable2D::setPosition(const float x, const float y)
    {
        mPosition.x = x;
        mPosition.y = y;
    }
    
    void Drawable2D::setPosition(const glm::vec2& p)
    {
        mPosition = p;
    }
    
    const glm::vec2& Drawable2D::getPosition() const
    {
        return mPosition;
    }

    void Drawable2D::translate(const float x, const float y)
    {
        mPosition += glm::vec2(x, y);
    }
    
    void Drawable2D::translate(const glm::vec2& p)
    {
        mPosition += p;
    }
    
    void Drawable2D::setOrigin(const float x, const float y)
    {
        mOrigin = glm::vec2(x, y);
    }

    void Drawable2D::setOrigin(const glm::vec2& p)
    {
        mOrigin = p;
    }

    const glm::vec2& Drawable2D::getOrigin() const
    {
        return mOrigin;
    }

    void Drawable2D::setRotation(const float radians)
    {
        mRotation = radians;
    }
    
    float Drawable2D::getRotation() const
    {
        return mRotation;
    }

    void Drawable2D::rotate(const float radians)
    {
        mRotation += radians;
    }

    void Drawable2D::setScale(const float x, const float y)
    {
        mScaling = glm::vec2(x, y);
    }

    void Drawable2D::setScale(const glm::vec2& s)
    {
        mScaling = s;
    }

    const glm::vec2& Drawable2D::getScale() const
    {
        return mScaling;
    }

    void Drawable2D::scale(const float x, const float y)
    {
        mScaling *= glm::vec2(x, y);
    }

    void Drawable2D::scale(const glm::vec2& s)
    {
        mScaling *= s;
    }
    
    void Drawable2D::setParallax(float p)
    {
        mParallax = p;
    }
    
    float Drawable2D::getParallax() const
    {
        return mParallax;
    }
        
    void Drawable2D::setColour(const Colour& c)
    {
        mColour = c;
    }
    
    Colour Drawable2D::getColour() const
    {
        return mColour;
    }
    
    void Drawable2D::setOpacity(float o)
    {
        mColour.setA(o);
    }

    float Drawable2D::getOpacity() const
    {
        return mColour.a();
    }

    RenderInfo Drawable2D::getRenderInfo() const
    {
        RenderInfo temp;
        std::hash<std::string> stringHasher;

        glm::vec3 colourInfo = glm::vec3(mColour.r(), mColour.g(), mColour.b());
        float opacity = mColour.a();

        temp.mDrawMode = mDrawMode;
        temp.mElementAmount = mVertices.size() / 2;

        temp.mVertexAttributes.push_back(VertexAttribute(stringHasher("vertex"), 2, &mVertices[0]));
        temp.mVertexAttributes.push_back(VertexAttribute(stringHasher("texCoords"), 2, &mTexCoords[0]));
        temp.mVertexAttributes.push_back(VertexAttribute(stringHasher("colours"), 4, &mVertexColours[0]));

        temp.mUniforms.push_back(Uniform(stringHasher("position"), VEC2, mPosition));
        temp.mUniforms.push_back(Uniform(stringHasher("origin"), VEC2, mOrigin));
        temp.mUniforms.push_back(Uniform(stringHasher("rotation"), FLOAT, mRotation));
        temp.mUniforms.push_back(Uniform(stringHasher("scaling"), VEC2, mScaling));
        temp.mUniforms.push_back(Uniform(stringHasher("parallax"), FLOAT, mParallax));
        //temp.uniforms.push_back(Uniform(stringHasher("texture"), TEXTURE, (GLuint)0)); maybe not needed
        temp.mUniforms.push_back(Uniform(stringHasher("constraints"), VEC4, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
        temp.mUniforms.push_back(Uniform(stringHasher("colour"), VEC3, colourInfo));
        temp.mUniforms.push_back(Uniform(stringHasher("opacity"), FLOAT, opacity));

        return temp;
    }
}
