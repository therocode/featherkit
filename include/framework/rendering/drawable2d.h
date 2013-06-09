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
            float getRotation() const;
            void rotate(const float radians);
            void setScale(const float x, const float y);
            void setScale(const glm::vec2& s);
            const glm::vec2& getScale() const;
            void scale(const float x, const float y);
            void scale(const glm::vec2& s);
        protected:
            std::vector<float> vertices;
            glm::vec2 position;
            float rotation = 0.0f;
            glm::vec2 scaling = glm::vec2(1.0f, 1.0f);

            glm::mat2x2 transformation;
    };
}
