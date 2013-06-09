#include <framework/rendering/quad.h>

namespace windbreeze
{
    Quad::Quad()
    {
        vertices = {-1.0f, -1.0f, 
                    -1.0f,  1.0f, 
                     1.0f,  1.0f, 
                     1.0f, -1.0f};
    }

    Quad::Quad(float w, float h)
    {
        float xnum = w * 0.5f;
        float ynum = h * 0.5f;

        vertices = {-xnum, -ynum, 
                    -xnum,  ynum, 
                     xnum,  ynum, 
                     xnum, -ynum};
    }
}
