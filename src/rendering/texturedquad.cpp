#include <framework/rendering/texturedquad.h>

namespace windbreeze
{
    TexturedQuad::TexturedQuad() : Quad::Quad()
    {
    }

    TexturedQuad::TexturedQuad(float w, float h) : Quad::Quad(w, h)
    {
    }

    TexturedQuad::TexturedQuad(float w, float h, float u, float v) : Quad::Quad(w, h)
    {
        textureCoordinates = glm::vec2(u, v);
    }
}
