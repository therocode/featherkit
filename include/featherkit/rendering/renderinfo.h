#pragma once
#include <featherkit/rendering/opengl.h>
#include <featherkit/rendering/uniform.h>
#include <featherkit/rendering/vertexattribute.h>
#include <vector>

namespace fea
{
    enum BlendMode { NONE = 0, ALPHA, ADD, MULTIPLY, MULTIPLY2X };

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
     *  @brief Contains the data needed for rendering a drawable.
     ***
     *  @var RenderInfo::uniforms
     *  @brief List of uniforms to use in the rendering process.
     ***
     *  @var RenderInfo::vertexAttributes
     *  @brief List of vertex attributes to use in the rendering process. The first one describes the vertex positions.
     ***
     *  @var RenderInfo::blendMode
     *  @brief Describes which blending mode the drawable should use.
     ***
     *  @var RenderInfo::drawMode
     *  @brief Describes which GL draw mode should be used to render the drawable.
     ***
     *  @var RenderInfo::elementAmount
     *  @brief Describes the amount of render elements 
     ***/
}
