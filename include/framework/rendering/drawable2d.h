#pragma once
#include <vector>
#include <framework/glm/glm.hpp>
#include <framework/rendering/renderdata.h>
#include <stdint.h>
#include <string>

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
            void setOrigin(const float x, const float y);
            void setOrigin(const glm::vec2& p);
            const glm::vec2& getOrigin() const;
            void setRotation(const float radians);
            float getRotation() const;
            void rotate(const float radians);
            void setScale(const float x, const float y);
            void setScale(const glm::vec2& s);
            const glm::vec2& getScale() const;
            void scale(const float x, const float y);
            void scale(const glm::vec2& s);
            void addTransformation(const glm::mat2x2& t);
            glm::mat2x2& getTransformation(uint32_t index);
            uint32_t getTransformationCount();
            void clearTransformations();
            virtual void getRenderData(RenderData& renderData) const;
        protected:
            std::vector<float> vertices;
            glm::vec2 position;
            glm::vec2 origin;
            float rotation = 0.0f;
            glm::vec2 scaling = glm::vec2(1.0f, 1.0f);

            std::vector<glm::mat2x2> transformations;
    };
}
