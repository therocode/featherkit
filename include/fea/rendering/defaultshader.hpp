#pragma once
#include <fea/config.hpp>
#include <string>

namespace fea
{
    struct FEA_API DefaultShader
    {
        static std::string vertexSource;
        static std::string fragmentSource;
    };
}
