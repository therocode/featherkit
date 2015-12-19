#include <fea/rendering/drawable2d.hpp>
#include <fea/assert.hpp>

namespace fea
{
    Drawable2D::Drawable2D() : mDrawMode(0), mRotation(0.0f), mScaling(glm::vec2(1.0f, 1.0f)), mParallax(glm::vec2(1.0f, 1.0f)), mColor(1.0f, 1.0f, 1.0f, 1.0f), mVerticesDirty(true), mUniformsDirty(true)
    {
        RenderEntity initialEntry;

        initialEntry.mDrawMode = mDrawMode;
        initialEntry.mElementAmount = 0;

        initialEntry.mVertexAttributes.emplace("vertex", VertexAttribute{2, {}});
        initialEntry.mVertexAttributes.emplace("texCoords", VertexAttribute{2, {}});
        initialEntry.mVertexAttributes.emplace("colors", VertexAttribute{4, {}});

        initialEntry.mUniforms.emplace("position", Uniform{VEC2, glm::vec2()});
        initialEntry.mUniforms.emplace("origin", Uniform{VEC2, glm::vec2()});
        initialEntry.mUniforms.emplace("rotation", Uniform{FLOAT, mRotation});
        initialEntry.mUniforms.emplace("scaling", Uniform{VEC2, glm::vec2()});
        initialEntry.mUniforms.emplace("parallax", Uniform{VEC2, glm::vec2()});
        initialEntry.mUniforms.emplace("constraints", Uniform{VEC4, glm::vec4()});
        initialEntry.mUniforms.emplace("color", Uniform{VEC3, glm::vec3()});
        initialEntry.mUniforms.emplace("opacity", Uniform{FLOAT, 0.0f});

        mRenderInfo.emplace_back(std::move(initialEntry));
    }

    const std::vector<float>& Drawable2D::getVertices() const
    {
        return mVertices;
    }
    
    void Drawable2D::setPosition(const glm::vec2& position)
    {
        mPosition = position;
        mUniformsDirty = true;
    }
    
    const glm::vec2& Drawable2D::getPosition() const
    {
        return mPosition;
    }
    
    void Drawable2D::translate(const glm::vec2& position)
    {
        mPosition += position;
        mUniformsDirty = true;
    }
    
    void Drawable2D::setOrigin(const glm::vec2& origin)
    {
        mOrigin = origin;
        mUniformsDirty = true;
    }

    const glm::vec2& Drawable2D::getOrigin() const
    {
        return mOrigin;
    }

    void Drawable2D::setRotation(const float radians)
    {
        mRotation = radians;
        mUniformsDirty = true;
    }
    
    float Drawable2D::getRotation() const
    {
        return mRotation;
    }

    void Drawable2D::rotate(const float radians)
    {
        mRotation += radians;
        mUniformsDirty = true;
    }

    void Drawable2D::setScale(const glm::vec2& scaling)
    {
        mScaling = scaling;
        mUniformsDirty = true;
    }

    const glm::vec2& Drawable2D::getScale() const
    {
        return mScaling;
    }

    void Drawable2D::scale(const glm::vec2& scaling)
    {
        mScaling *= scaling;
        mUniformsDirty = true;
    }

    void Drawable2D::setParallax(const glm::vec2& parallax)
    {
        mParallax = parallax;
        mUniformsDirty = true;
    }
    
    const glm::vec2& Drawable2D::getParallax() const
    {
        return mParallax;
    }
        
    void Drawable2D::setColor(const Color& color)
    {
        mColor = color;
        mUniformsDirty = true;
    }
    
    Color Drawable2D::getColor() const
    {
        return mColor;
    }
    
    void Drawable2D::setOpacity(float opacity)
    {
        FEA_ASSERT(opacity >= 0.0f && opacity <= 1.0f, "Opacity must be within the range of [0.0f, 1.0f]! " + std::to_string(opacity) + " provided.");
        mColor.setAAsFloat(opacity);
        mUniformsDirty = true;
    }

    float Drawable2D::getOpacity() const
    {
        return mColor.aAsFloat();
    }

    const std::vector<RenderEntity>& Drawable2D::getRenderInfo() const
    {
        if(mVerticesDirty || mUniformsDirty)
        {
            updateRenderInfo(mRenderInfo, mVerticesDirty, mUniformsDirty);
            mVerticesDirty = false;
            mUniformsDirty = false;
        }

        return mRenderInfo;
    }

    void Drawable2D::updateRenderInfo(std::vector<RenderEntity>& renderInfo, bool updateVertices, bool updateUniforms) const
    {
        RenderEntity& renderEntity = renderInfo.front();

        if(updateVertices)
        {
            renderEntity.mDrawMode = mDrawMode;
            renderEntity.mElementAmount = 0; //this could be worked out correctly from drawmode. it must now be set in the child

            renderEntity.mVertexAttributes.at("vertex") = VertexAttribute{2, mVertices};
            renderEntity.mVertexAttributes.at("texCoords") = VertexAttribute{2, mTexCoords};
            renderEntity.mVertexAttributes.at("colors") = VertexAttribute{4, mVertexColors};
        }

        if(updateUniforms)
        {
            renderEntity.mUniforms.at("position") = Uniform{VEC2, mPosition};
            renderEntity.mUniforms.at("origin") = Uniform{VEC2, mOrigin};
            renderEntity.mUniforms.at("rotation") = Uniform{FLOAT, mRotation};
            renderEntity.mUniforms.at("scaling") = Uniform{VEC2, mScaling};
            renderEntity.mUniforms.at("parallax") = Uniform{VEC2, mParallax};
            renderEntity.mUniforms.at("constraints") = Uniform{VEC4, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)};
            glm::vec3 colorInfo = glm::vec3(mColor.rAsFloat(), mColor.gAsFloat(), mColor.bAsFloat());
            renderEntity.mUniforms.at("color") = Uniform{VEC3, colorInfo};
            float opacity = mColor.aAsFloat();
            renderEntity.mUniforms.at("opacity") = Uniform{FLOAT, opacity};
        }
    }

}
