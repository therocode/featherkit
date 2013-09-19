#pragma once
#include <featherkit/rendering/opengl.h>
#include <featherkit/rendering/uniform.h>
#include <featherkit/rendering/vertexattribute.h>
#include <vector>

namespace fea
{
    enum BlendMode { NONE, ALPHA, ADD, MULTIPLY, MULTIPLY2X };

    struct RenderInfo
    {
        uint32_t getDrawAmount() const;
        std::vector<Uniform> uniforms;
        std::vector<VertexAttribute> vertexAttributes;
        BlendMode blendMode;
        GLenum drawMode;
    };
}
