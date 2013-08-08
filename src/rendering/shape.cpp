#include <featherkit/rendering/shape.h>

namespace fea
{
    Shape::Shape() : texture(nullptr)
    {
    }

    void Shape::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Drawable2D::getRenderData(renderData, time);

        if(texture != nullptr)
            renderData.texture = getTexture().getId();

        renderData.texCoords = texCoords;
    }
    
    void Shape::setTexture(const Texture& tex)
    {
        texture = &tex;
    }

    const Texture& Shape::getTexture() const
    {
        return *texture;
    }
    
    void Shape::setVertices(const std::vector<float>& vert, const std::vector<float>& tex)
    {
        vertices = vert;
        texCoords = tex;
    }
}
