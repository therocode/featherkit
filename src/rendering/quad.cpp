#include <featherkit/rendering/quad.h>

namespace fea
{
    Quad::Quad() : mHFlip(1.0f), mVFlip(1.0f), mTexture(nullptr)
    {
        mVertices = {-1.0f, -1.0f, 
                    -1.0f,  1.0f, 
                     1.0f, -1.0f, 
                     1.0f, -1.0f, 
                    -1.0f,  1.0f, 
                     1.0f,  1.0f};
        mOrigin = glm::vec2(-1.0f, -1.0f);

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f);
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f);

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        mVertexColours = {0.0f, 0.0f, 0.0f, 0.0f,
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
        float xnum = size.x * 0.5f;
        float ynum = size.y * 0.5f;

        mVertices = {-xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum, -ynum, 
                     xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum,  ynum};
        mOrigin = glm::vec2(-xnum, -ynum);

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f);
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f);

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        mVertexColours = {0.0f, 0.0f, 0.0f, 0.0f,
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
        float xnum = size.x * 0.5f;
        float ynum = size.y * 0.5f;

        mVertices = {-xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum, -ynum, 
                     xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum,  ynum};
        mOrigin = glm::vec2(-xnum, -ynum);
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
