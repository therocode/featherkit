#pragma once
#include <string>

namespace windbreeze
{
    struct RenderData
    {
        std::vector<float> vertices;
        std::string textureId;
        std::vector<float> texCoords;
        glm::vec2 constrainX = glm::vec2(1.0f, 0.0f);
        glm::vec2 constrainY = glm::vec2(1.0f, 0.0f);
        glm::vec2 textureScroll;
        float parallax = 1.0f;
    };
}
