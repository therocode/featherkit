#pragma once
#include <framework/rendering/quad.h>

namespace windbreeze
{
    class TexturedQuad : public Quad
    {
        public:
            TexturedQuad();
            TexturedQuad(float w, float h);
            TexturedQuad(float w, float h, float u, float v);
        protected:
            glm::vec2 textureCoordinates;
    };
}
