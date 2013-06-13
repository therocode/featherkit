#pragma once
#include <framework/glm/glm.hpp>

namespace windbreeze
{
    class Camera
    {
        public:
            Camera(float x, float y);
            Camera(float x, float y, float xZoom, float yZoom);
            Camera(glm::vec2 position);
            Camera(glm::vec2 position, glm::vec2 zoom);
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
            glm::vec2 transformPoint(const glm::vec2 point);
        private:
            glm::vec2 position;
            glm::vec2 zoom;
            float rotation = 0.0f;
    };
}
