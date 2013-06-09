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
            
    glm::vec2 Quad::getSize()
    {
        return glm::vec2(vertices[0] * 2.0f, vertices[1] * 2.0f);
    }
}
