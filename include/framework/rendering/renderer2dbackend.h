#pragma once
#include <vector>
#include <framework/glm/glm.hpp>
#include <framework/rendering/viewport.h>
#include <string>

namespace windbreeze
{
    struct RenderData
    {
        std::vector<float> vertices;
        std::string textureId;
        std::vector<float> texCoords;
    };

    class Renderer2DBackend
    {
        public:
            virtual void setup() = 0;
            virtual void destroy() = 0;
            virtual void clear() = 0;
            virtual void render(RenderData renderData) = 0;
            void setViewport(const Viewport& v);
        protected:
            Viewport viewport;
    };
}
