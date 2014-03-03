#pragma once
#include <featherkit/rendering/opengl.hpp>
#include <featherkit/rendering/uniform.hpp>
#include <featherkit/rendering/vertexattribute.hpp>
#include <vector>

namespace fea
{
    enum BlendMode { NONE = 0, ALPHA, ADD, MULTIPLY, MULTIPLY2X };

    struct RenderInfo
    {
        std::vector<Uniform> mUniforms;
        std::vector<VertexAttribute> mVertexAttributes;
        BlendMode mBlendMode;
        GLenum mDrawMode;
        uint32_t mElementAmount;
    };
    /** @addtogroup Render2D
     *@{
     *  @class RenderInfo
     *@}
     ***
     *  @class RenderInfo
     *  @brief Contains the data needed for rendering a drawable.
     ***
     *  @var RenderInfo::mUniforms
     *  @brief List of uniforms to use in the rendering process.
     ***
     *  @var RenderInfo::mVertexAttributes
     *  @brief List of vertex attributes to use in the rendering process. The first one describes the vertex positions.
     ***
     *  @var RenderInfo::mBlendMode
     *  @brief Describes which blending mode the drawable should use.
     ***
     *  @var RenderInfo::mDrawMode
     *  @brief Describes which GL draw mode should be used to render the drawable.
     ***
     *  @var RenderInfo::mElementAmount
     *  @brief Describes the amount of render elements 
     ***/
}
