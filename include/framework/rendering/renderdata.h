#pragma once
#include <string>

namespace windbreeze
{
    struct RenderData
    {
        std::vector<float> vertices;
        std::string textureId;
        std::vector<float> texCoords;
    };
}
