#pragma once
#include <framework/rendering/renderer2dbackend.h>
#include <SFML/OpenGL.hpp>

namespace windbreeze
{
    class Sfml2DBackend : public Renderer2DBackend
    {
        public:
            void setup() override;
            void destroy() override;
            void clear() override;
            void render(RenderData renderData) override;
    };
}
