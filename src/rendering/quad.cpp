#include <featherkit/rendering/quad.h>

namespace fea
{
    Quad::Quad() : mHFlip(1.0f), mVFlip(1.0f), mTexture(nullptr)
    {
        vertices = {-1.0f, -1.0f, 
                    -1.0f,  1.0f, 
                     1.0f, -1.0f, 
                     1.0f, -1.0f, 
                    -1.0f,  1.0f, 
                     1.0f,  1.0f};
        origin = glm::vec2(-1.0f, -1.0f);

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f);
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f);

        texCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        vertexColours = {0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f};

        drawMode = GL_TRIANGLES;
        mContraints = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }

    Quad::Quad(float w, float h) : mHFlip(1.0f), mVFlip(1.0f), mTexture(nullptr)
    {
        float xnum = w * 0.5f;
        float ynum = h * 0.5f;

        vertices = {-xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum, -ynum, 
                     xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum,  ynum};
        origin = glm::vec2(-xnum, -ynum);

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f);
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f);

        texCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        vertexColours = {0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f};

        drawMode = GL_TRIANGLES;
        mContraints = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    
    Quad::Quad(const glm::vec2& size) : Quad(size.x, size.y)
    {
    }
    
    void Quad::setSize(float w, float h)
    {
        float xnum = w * 0.5f;
        float ynum = h * 0.5f;

        vertices = {-xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum, -ynum, 
                     xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum,  ynum};
        origin = glm::vec2(-xnum, -ynum);
    }

    void Quad::setSize(glm::vec2 size)
    {
        setSize(size.x, size.y);
    }
            
    glm::vec2 Quad::getSize() const
    {
        return glm::vec2(vertices[4] * 2.0f, vertices[3] * 2.0f);
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

        texCoords =  {texCoordsX[0], texCoordsY[0],
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

        texCoords =  {texCoordsX[0], texCoordsY[0],
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
            temp.uniforms.push_back(Uniform(stringHasher("texture"), TEXTURE, getTexture().getId()));
        }

        temp.uniforms.push_back(Uniform(stringHasher("constraints"), VEC4, mContraints));
        
        return temp;
    }
}
