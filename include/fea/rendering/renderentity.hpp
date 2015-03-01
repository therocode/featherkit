#pragma once
#include <fea/config.hpp>
#include <fea/rendering/opengl.hpp>
#include <fea/rendering/uniform.hpp>
#include <fea/rendering/vertexattribute.hpp>
#include <vector>

namespace fea
{
    enum BlendMode { NONE = 0, ALPHA, ADD, MULTIPLY, MULTIPLY2X };

    struct FEA_API RenderEntity
    {
        std::vector<Uniform> mUniforms;
        std::vector<VertexAttribute> mVertexAttributes;
        BlendMode mBlendMode;
        GLenum mDrawMode;
        uint32_t mElementAmount;
    };
    /** @addtogroup Rendering
     *@{
     *  @enum BlendMode
     *  @class RenderEntity
     *@}
     ***
     *  @enum BlendMode
     *  @brief Mode the renderer uses for blending colors.
     ***
     *  @class RenderEntity
     *  @brief Contains the data needed for rendering a drawable.
     ***
     *  @var RenderEntity::mUniforms
     *  @brief List of uniforms to use in the rendering process.
     ***
     *  @var RenderEntity::mVertexAttributes
     *  @brief List of vertex attributes to use in the rendering process. The first one describes the vertex positions.
     ***
     *  @var RenderEntity::mBlendMode
     *  @brief Describes which blending mode the drawable should use.
     ***
     *  @var RenderEntity::mDrawMode
     *  @brief Describes which GL draw mode should be used to render the drawable.
     ***
     *  @var RenderEntity::mElementAmount
     *  @brief Describes the amount of render elements 
     ***/
}
