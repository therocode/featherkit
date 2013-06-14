#pragma once
#include <vector>
#include <framework/glm/glm.hpp>

namespace windbreeze
{
    struct RenderData
    {
        std::vector<float> vertices;
    };

    class Renderer2DBackend
    {
        public:
            virtual void setup() = 0;
            virtual void destroy() = 0;
            virtual void clear() = 0;
            virtual void render(RenderData renderData) = 0;
            void setCameraPosition(glm::vec2 position);
            void setCameraZoom(glm::vec2 zoom);
            void setCameraTransform(glm::mat2x2 transform);
            void setViewSize(glm::vec2 size);
        protected:
            glm::vec2 cameraPosition;
            glm::vec2 cameraZoom = glm::vec2(1.0f, 1.0f);
            glm::mat2x2 cameraTransform;
            glm::vec2 viewSize;
    };
}
