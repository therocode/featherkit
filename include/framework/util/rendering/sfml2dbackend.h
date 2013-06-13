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
            void setViewRect(float x, float y, float w, float h) override;
            void setViewTransform(glm::mat2x2 transform) override;
            void render(RenderData renderData) override;
        private:
            glm::vec2 viewSize;
            glm::mat2x2 viewTransform;
    };
}
