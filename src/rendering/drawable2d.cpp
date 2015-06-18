#include <fea/rendering/drawable2d.hpp>
#include <fea/assert.hpp>

namespace fea
{
    Drawable2D::Drawable2D() : mDrawMode(0), mRotation(0.0f), mScaling(glm::vec2(1.0f, 1.0f)), mParallax(glm::vec2(1.0f, 1.0f)), mColor(1.0f, 1.0f, 1.0f, 1.0f)
    {
    }

    const std::vector<float>& Drawable2D::getVertices() const
    {
        return mVertices;
    }
    
    void Drawable2D::setPosition(const glm::vec2& position)
    {
        mPosition = position;
    }
    
    const glm::vec2& Drawable2D::getPosition() const
    {
        return mPosition;
    }
    
    void Drawable2D::translate(const glm::vec2& position)
    {
        mPosition += position;
    }
    
    void Drawable2D::setOrigin(const glm::vec2& origin)
    {
        mOrigin = origin;
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

    void Drawable2D::setScale(const glm::vec2& scaling)
    {
        mScaling = scaling;
    }

    const glm::vec2& Drawable2D::getScale() const
    {
        return mScaling;
    }

    void Drawable2D::scale(const glm::vec2& scaling)
    {
        mScaling *= scaling;
    }

    void Drawable2D::setParallax(const glm::vec2& parallax)
    {
        mParallax = parallax;
    }
    
    const glm::vec2& Drawable2D::getParallax() const
    {
        return mParallax;
    }
        
    void Drawable2D::setColor(const Color& color)
    {
        mColor = color;
    }
    
    Color Drawable2D::getColor() const
    {
        return mColor;
    }
    
    void Drawable2D::setOpacity(float opacity)
    {
        FEA_ASSERT(opacity >= 0.0f && opacity <= 1.0f, "Opacity must be within the range of [0.0f, 1.0f]! " + std::to_string(opacity) + " provided.");
        mColor.setAAsFloat(opacity);
    }

    float Drawable2D::getOpacity() const
    {
        return mColor.aAsFloat();
    }

    std::vector<RenderEntity> Drawable2D::getRenderInfo() const
    {
        RenderEntity temp;

        glm::vec3 colorInfo = glm::vec3(mColor.rAsFloat(), mColor.gAsFloat(), mColor.bAsFloat());
        float opacity = mColor.aAsFloat();

        temp.mDrawMode = mDrawMode;
        temp.mElementAmount = mVertices.size() / 2;

        if(mVertices.size() > 0)
            temp.mVertexAttributes.push_back(VertexAttribute("vertex", 2, mVertices));
        if(mTexCoords.size() > 0)
            temp.mVertexAttributes.push_back(VertexAttribute("texCoords", 2, mTexCoords));
        if(mVertexColors.size() > 0)
            temp.mVertexAttributes.push_back(VertexAttribute("colors", 4, mVertexColors));

        temp.mUniforms.push_back(Uniform("position", VEC2, mPosition));
        temp.mUniforms.push_back(Uniform("origin", VEC2, mOrigin));
        temp.mUniforms.push_back(Uniform("rotation", FLOAT, mRotation));
        temp.mUniforms.push_back(Uniform("scaling", VEC2, mScaling));
        temp.mUniforms.push_back(Uniform("parallax", VEC2, mParallax));
        temp.mUniforms.push_back(Uniform("constraints", VEC4, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
        temp.mUniforms.push_back(Uniform("color", VEC3, colorInfo));
        temp.mUniforms.push_back(Uniform("opacity", FLOAT, opacity));

        for(const auto& uniform : mExtraUniforms)
            temp.mUniforms.push_back(uniform.second);

        return {temp};
    }

    void Drawable2D::setExtraUniform(const Uniform& uniform)
    {
        mExtraUniforms[uniform.mName] = uniform;
    }

    bool Drawable2D::hasExtraUniform(const std::string& name) const
    {
        return mExtraUniforms.find(name) != mExtraUniforms.end();
    }

    const Uniform& Drawable2D::getExtraUniform(const std::string& name) const
    {
        FEA_ASSERT(mExtraUniforms.find(name) != mExtraUniforms.end(), "Trying to access a uniform called " << name << " which doesn't exist");
        return mExtraUniforms.at(name);
    }
    
    void Drawable2D::removeExtraUniform(const std::string& name)
    {
        FEA_ASSERT(mExtraUniforms.find(name) != mExtraUniforms.end(), "Trying to erase a uniform called " << name << " which doesn't exist");
        mExtraUniforms.erase(name);
    }

    void Drawable2D::clearExtraUniforms()
    {
        mExtraUniforms.clear();
    }
}
