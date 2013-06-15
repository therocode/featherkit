#include <framework/rendering/quad.h>

namespace windbreeze
{
    Quad::Quad()
    {
        vertices = {-1.0f, -1.0f, 
                    -1.0f,  1.0f, 
                     1.0f,  1.0f, 
                     1.0f, -1.0f};
        origin = glm::vec2(-1.0f, -1.0f);
    }

    Quad::Quad(float w, float h)
    {
        float xnum = w * 0.5f;
        float ynum = h * 0.5f;

        vertices = {-xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum,  ynum, 
                     xnum, -ynum};
        origin = glm::vec2(-xnum, -ynum);
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
        return glm::vec2(vertices[0] * 2.0f, vertices[1] * 2.0f);
    }
    
    void Quad::setTexture(const std::string& tex)
    {
        textureId = tex;
    }

    const std::string& Quad::getTexture() const
    {
        return textureId;
    }

    void Quad::getRenderData(RenderData& renderData) const
    {
        Drawable2D::getRenderData(renderData);

        renderData.textureId = getTexture();
        renderData.texCoords =  {0.0f, 1.0f,
                                 1.0f, 1.0f,
                                 1.0f, 0.0f,
                                 0.0f, 0.0f};
    }
}
