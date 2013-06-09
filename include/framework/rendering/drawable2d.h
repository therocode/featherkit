#pragma once
#include <vector>
#include <framework/glm/glm.hpp>

namespace windbreeze
{
    class Drawable2D
    {
        public:
            const std::vector<float>& getVertices() const;
            std::vector<float> getVerticesTransformed() const;
            void setPosition(const float x, const float y);
            void setPosition(const glm::vec2& p);
            const glm::vec2& getPosition() const;
            void translate(const float x, const float y);
            void translate(const glm::vec2& p);
            void setRotation(const float radians);
            float getRotation();
            void rotate(const float radians);
        protected:
            std::vector<float> vertices;
            glm::vec2 position;
            float rotation = 0;
            glm::mat2x2 transformation;
    };
}
