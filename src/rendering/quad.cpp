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
}
