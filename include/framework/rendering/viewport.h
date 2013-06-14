#pragma once
#include <framework/rendering/camera.h>
#include <stdint.h>

namespace windbreeze
{
    class Viewport
    {
        public:
            Viewport() {}
            Viewport(uint32_t w, uint32_t h) : size(glm::uvec2(w, h)) {}
            Viewport(uint32_t w, uint32_t h, const Camera& cam) : size(glm::uvec2(w, h)), camera(cam) {}
            void setSize(const glm::uvec2& s);
            glm::uvec2& getSize();
            void setCamera(const Camera& cam);
            Camera& getCamera();
            glm::vec2 transformPoint(const glm::vec2 point);
            glm::vec2 untransformPoint(const glm::vec2 point);
        private:
            glm::uvec2 size;
            Camera camera;
    };
}
