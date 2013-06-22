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

    struct TextData
    {
        std::string text;
        glm::vec2 position;
        glm::vec3 colour;
        float size;
        int font = 0;
    };

    struct AABB
    {
        glm::vec2 start;
        glm::vec2 end;
    };
}
