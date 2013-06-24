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
    /** @addtogroup Render2D
     *@{
     *  @struct RenderData
     *  @struct TextData
     *  @struct AABB
     *@}
     ***
     *  @struct RenderData
     *  @brief Container for render data, passed by the Render2D to the Renderer2DBackend.
     ***
     *  @var RenderData::vertices
     *  @brief Vertices of what is to be rendered.
     ***
     *  @var RenderData::textureId
     *  @brief Name of the texture to use.
     ***
     *  @var RenderData::texCoords
     *  @brief Texture coordinates for the object.
     ***
     *  @var RenderData::constrainX
     *  @brief Upper and lower border on the X axis of the rectangle on the texture in which the intended texture lies.
     ***
     *  @var RenderData::constrainY
     *  @brief Upper and lower border on the Y axis of the rectangle on the texture in which the intended texture lies.
     ***
     *  @var RenderData::textureScroll
     *  @brief Vector describing an offset of the texture to be used.
     ***
     *  @var RenderData::parallax
     *  @brief Parallax factor of the object.
     ***
     *  @struct TextData
     *  @brief Container for text object data, passed by the Render2D to the Renderer2DBackend. Contains needed information to perform text rendering.
     ***
     *  @var TextData::text
     *  @brief Text to render.
     ***
     *  @var TextData::position
     *  @brief Location in world space of the rendered text.
     ***
     *  @var TextData::colour
     *  @brief Colour of the text.
     ***
     *  @var TextData::size
     *  @brief Size of the text.
     ***
     *  @var TextData::font
     *  @brief ID of the font to use.
     ***
     *  @struct AABB
     *  @brief Axis Aligned Bounding Box. A rectangle aligned to the X and Y axes.
     ***
     *  @var AABB::start
     *  @brief Vector describing the upper left corner of the box.
     ***
     *  @var AABB::end
     *  @breif Vector describing the bottom right corner of the box.
     ***/
}
