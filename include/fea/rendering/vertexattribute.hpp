#pragma once
#include <cstdint>
#include <cstddef>
#include <string>

namespace fea
{
    enum VertexAttributeType{AVEC2, AVEC4};

    struct VertexAttribute
    {
        VertexAttribute(const std::string& name, const uint32_t floatAmount, const float* data);
        std::string mName;
        uint32_t mFloatAmount;
        const float* mData;
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
     *  @fn VertexAttribute::VertexAttribute(const std::string& name, const uint32_t floatAmount, const float* data)
     *  @brief Construct a vertex attribute.
     *  @param name name;
     *  @param floatAmount Amount of floats.
     *  @param data Float array.
     ***
     *  @var VertexAttribute::mName
     *  @brief Name of the attribute.
     ***
     *  @var VertexAttribute::mFloatAmount
     *  @brief Amount of floats in the data array.
     ***
     *  @var VertexAttribute::mData
     *  @brief Data array.
     ***/
}
