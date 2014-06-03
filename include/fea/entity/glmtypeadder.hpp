#pragma once
#include <fea/config.hpp>

namespace fea
{
    class EntityFactory;

    void FEA_API addGlmDataTypes(EntityFactory& factory);

    /** @addtogroup EntitySystem
     *@{
     *  @fn void addGlmDataTypes(EntityFactory& factory)
     *  @brief Register standard glm data types to use with the EntityFactory.
     *  
     *  All types registered provide a parser for setting default values.
     *
     *  There are three categories of the types registered by this function.
     *
     *  <b>Floating point vectors</b>
     *  - "vec2"
     *  - "vec3"
     *  
     *  The parser for floating point vectors takes two decimal numbers separated by comma where each follows the convention of std::stof and std::stod respectively.
     *
     *  <b>Integer vectors</b>
     *  - "ivec2"
     *  - "uvec2"
     *  - "ivec3"
     *  - "uvec3"
     *
     *  The parser for integer type vectors takes two integer numbers separated by comma where each follows the convention of the std string-to-int parsing functions (std::stoi and the like) with additional range checks.
     *
     *  <b>Matrices</b>
     *  - "mat2x2"
     *  - "mat3x3"
     *  - "mat4x4"
     *
     *  The matrices are all floating point matrices. The parsers take as many decimal numbers as elements in the matrix, separated by comma, or a single "I" to create an identity matrix.
     *@}
     ***/
}
