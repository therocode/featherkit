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
        protected:
            std::vector<float> vertices;
            glm::vec2 position;
            glm::mat2x2 transformation;
    };
}
