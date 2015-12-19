#pragma once
#include <fea/config.hpp>
#include <fea/rendering/opengl.hpp>
#include <fea/rendering/uniform.hpp>
#include <fea/rendering/vertexattribute.hpp>
#include <unordered_map>

namespace fea
{
    enum BlendMode { NONE = 0, ALPHA, ADD, MULTIPLY, MULTIPLY2X };

    struct FEA_API RenderEntity
    {
        std::unordered_map<std::string, Uniform> mUniforms;
        std::unordered_map<std::string, VertexAttribute> mVertexAttributes;
        GLenum mDrawMode;
        uint32_t mElementAmount;
    };
    /** @addtogroup Render2D
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
     *  @brief Map of uniforms to use in the rendering process.
     ***
     *  @var RenderEntity::mVertexAttributes
     *  @brief Map of vertex attributes to use in the rendering process.
     ***
     *  @var RenderEntity::mDrawMode
     *  @brief Describes which GL draw mode should be used to render the drawable.
     ***
     *  @var RenderEntity::mElementAmount
     *  @brief Describes the amount of render elements 
     ***/
}
