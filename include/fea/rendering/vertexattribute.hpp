#pragma once
#include <fea/config.hpp>
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

namespace fea
{
    enum VertexAttributeType{AVEC2, AVEC4};

    struct FEA_API VertexAttribute
    {
        VertexAttribute(uint32_t floatAmount, std::vector<float> data);
        uint32_t mAttributeFloatAmount;
        std::vector<float> mData;
    };
    /** @addtogroup Render2D
     *@{
     *  @class VertexAttribute
     *  @enum VertexAttributeType
     *@}
     ***
     *  @class VertexAttribute
     *  @brief Defines a vertex attribute.
     ***
     *  @enum VertexAttributeType
     *  @brief Type of the attribute.
     ***
     *  @fn VertexAttribute::VertexAttribute(uint32_t floatAmount, std::vector<float> data)
     *  @brief Construct a vertex attribute.
     *  @param mAttributeFloatAmount Amount of floats per attribute
     *  @param mData Float array.
     ***
     *  @var VertexAttribute::mAttributeFloatAmount
     *  @brief The amount of floats per attribute. For example, a 2D coordinate would have 2 (x and y), and a colour would have 4 (r, g, b and a).
     ***
     *  @var VertexAttribute::mData
     *  @brief Data array.
     ***/
}
