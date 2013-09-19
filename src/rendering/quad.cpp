#include <featherkit/rendering/quad.h>
#include <iostream>

namespace fea
{
    Quad::Quad() : hFlip(1.0f), vFlip(1.0f), texture(nullptr)
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
    }

    Quad::Quad(float w, float h) : hFlip(1.0f), vFlip(1.0f), texture(nullptr)
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
        texture = &tex;
    }

    const Texture& Quad::getTexture() const
    {
        return *texture;
    }

    void Quad::setHFlip(bool enabled)
    {
        if(enabled)
            hFlip = -1.0f;
        else
            hFlip = 1.0f;

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * hFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * vFlip;

        texCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};
    }

    void Quad::setVFlip(bool enabled)
    {
        if(enabled)
            vFlip = -1.0f;
        else
            vFlip = 1.0f;
    }
    
    RenderInfo Quad::getRenderInfo() const
    {
        RenderInfo temp = Drawable2D::getRenderInfo();
        std::hash<std::string> stringHasher;

        if(texture != nullptr)
            temp.uniforms.push_back(Uniform(stringHasher("texture"), TEXTURE, getTexture().getId()));

        temp.vertexAttributes.push_back(VertexAttribute(stringHasher("texCoords"), &texCoords[0])); //ajaj?
        
        return temp;
    }
}
