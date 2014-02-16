#pragma once
#include <cstdint>
#include <cstddef>

namespace fea
{
    enum VertexAttributeType{AVEC2, AVEC4};

    struct VertexAttribute
    {
        VertexAttribute(size_t i, const uint32_t floatAmount, const float* data);
        size_t mIndex;
        uint32_t mFloatAmount;
        const float* mData;
    };
    /** @addtogroup Renderer2D
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
     *  @fn VertexAttribute::VertexAttribute(size_t i, const uint32_t floatAmount, const float* data)
     *  @brief Construct a vertex attribute.
     *  @param i Index.
     *  @param floatAmount Amount of floats.
     *  @param data Float array.
     ***
     *  @var VertexAttribute::mIndex
     *  @brief Index of the attribute.
     ***
     *  @var VertexAttribute::mFloatAmount
     *  @brief Amount of floats in the data array.
     ***
     *  @var VertexAttribute::mData
     *  @brief Data array.
     ***/
}
