#pragma once
#include <framework/glm/glm.hpp>

namespace windbreeze
{
    class Camera
    {
        public:
            Camera() : position(glm::vec2(0.0f, 0.0f)), zoom(glm::vec2(1.0f, 1.0f)) {}
            Camera(float x, float y) : position(glm::vec2(x, y)), zoom(glm::vec2(1.0f, 1.0f)) {}
            Camera(float x, float y, float xZoom, float yZoom) : position(glm::vec2(x, y)), zoom(glm::vec2(xZoom, yZoom)) {}
            Camera(glm::vec2 p) : position(p), zoom(glm::vec2(1.0f, 1.0f)) {}
            Camera(glm::vec2 p, glm::vec2 z) : position(p), zoom(z) {}
            void setPosition(float x, float y);
            void setPosition(glm::vec2 p);
            const glm::vec2& getPosition();
            void translate(float x, float y);
            void translate(glm::vec2 p);
            void setZoom(float x, float y);
            void setZoom(glm::vec2 z);
            const glm::vec2& getZoom();
            void setRotation(float radians);
            void rotate(float radians);
            glm::mat2x2 getTransformation();
        private:
            glm::vec2 position;
            glm::vec2 zoom;
            float rotation = 0.0f;
    };
}
