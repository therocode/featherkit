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
        std::vector<Uniform> uniforms;
        std::vector<VertexAttribute> vertexAttributes;
        BlendMode blendMode;
        GLenum drawMode;
        uint32_t elementAmount;
    };
    /** @addtogroup Render2D
     *@{
     *  @class RenderInfo
     *@}
     ***
     *  @class RenderInfo
     *  @brief Contains
     ***/
}
