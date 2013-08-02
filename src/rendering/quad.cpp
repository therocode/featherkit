#include <featherkit/rendering/quad.h>

namespace fea
{
    Quad::Quad() : hFlip(1.0f), vFlip(1.0f)
    {
        vertices = {-1.0f, -1.0f, 
                    -1.0f,  1.0f, 
                     1.0f,  1.0f, 
                     1.0f, -1.0f};
        origin = glm::vec2(-1.0f, -1.0f);
    }

    Quad::Quad(float w, float h) : hFlip(1.0f), vFlip(1.0f)
    {
        float xnum = w * 0.5f;
        float ynum = h * 0.5f;

        vertices = {-xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum,  ynum, 
                     xnum, -ynum};
        origin = glm::vec2(-xnum, -ynum);
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
                     xnum,  ynum, 
                     xnum, -ynum};
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
    
    void Quad::setTexture(const std::string& tex)
    {
        textureId = tex;
    }

    const std::string& Quad::getTexture() const
    {
        return textureId;
    }

    void Quad::setHFlip(bool enabled)
    {
        if(enabled)
            hFlip = -1.0f;
        else
            hFlip = 1.0f;
    }

    void Quad::setVFlip(bool enabled)
    {
        if(enabled)
            vFlip = -1.0f;
        else
            vFlip = 1.0f;
    }

    void Quad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Drawable2D::getRenderData(renderData, time);

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * hFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * vFlip;


        renderData.textureId = getTexture();
        renderData.texCoords =  {texCoordsX[0], texCoordsY[0],
                                 texCoordsX[0], texCoordsY[1],
                                 texCoordsX[1], texCoordsY[1],
                                 texCoordsX[1], texCoordsY[0]};
    }
}
