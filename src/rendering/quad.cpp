#include <featherkit/rendering/quad.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    Quad::Quad() : mHFlip(1.0f), mVFlip(1.0f), mTexture(nullptr)
    {
        mVertices = {0.0f, 0.0f, 
                    0.0f,  1.0f, 
                     1.0f, 0.0f, 
                     1.0f, 0.0f, 
                    0.0f,  1.0f, 
                     1.0f,  1.0f};

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f);
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f);

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        mVertexColors = {0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f};

        mDrawMode = GL_TRIANGLES;
        mConstraints = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }

    Quad::Quad(const glm::vec2& size) : mHFlip(1.0f), mVFlip(1.0f), mTexture(nullptr)
    {
        FEA_ASSERT(size.x > 0.0f && size.y > 0.0f, "Size of quads must be bigger than zero in all dimensions! " + std::to_string(size.x) + " " + std::to_string(size.y) + " provided.");
        float xnum = size.x;
        float ynum = size.y;

        mVertices = {0.0f, 0.0f, 
                     0.0f, ynum, 
                     xnum, 0.0f, 
                     xnum, 0.0f, 
                     0.0f, ynum, 
                     xnum, ynum};

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f);
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f);

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        mVertexColors = {0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f};

        mDrawMode = GL_TRIANGLES;
        mConstraints = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    
    void Quad::setSize(const glm::vec2& size)
    {
        FEA_ASSERT(size.x > 0.0f && size.y > 0.0f, "Size of quads must be bigger than zero in all dimensions! " + std::to_string(size.x) + " " + std::to_string(size.y) + " provided.");
        float xnum = size.x;
        float ynum = size.y;

        mVertices = {0.0f, 0.0f, 
                     0.0f, ynum, 
                     xnum, 0.0f, 
                     xnum, 0.0f, 
                     0.0f, ynum, 
                     xnum, ynum};
    }

    glm::vec2 Quad::getSize() const
    {
        return glm::vec2(mVertices[4] * 2.0f, mVertices[3] * 2.0f);
    }
    
    void Quad::setTexture(const Texture& tex)
    {
        mTexture = &tex;
    }

    const Texture& Quad::getTexture() const
    {
        return *mTexture;
    }

    void Quad::setHFlip(bool enabled)
    {
        if(enabled)
            mHFlip = -1.0f;
        else
            mHFlip = 1.0f;

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * mHFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * mVFlip;

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};
                      
                      //Make nice
    }

    void Quad::setVFlip(bool enabled)
    {
        if(enabled)
            mVFlip = -1.0f;
        else
            mVFlip = 1.0f;

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * mHFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * mVFlip;

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};
    }
    
    RenderInfo Quad::getRenderInfo() const
    {
        RenderInfo temp = Drawable2D::getRenderInfo();
        std::hash<std::string> stringHasher;

        if(mTexture != nullptr)
        {
            temp.mUniforms.push_back(Uniform(stringHasher("texture"), TEXTURE, getTexture().getId()));
        }

        temp.mUniforms.push_back(Uniform(stringHasher("constraints"), VEC4, mConstraints));
        
        return temp;
    }
}
