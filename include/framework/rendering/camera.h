#include <framework/glm/glm.hpp>

namespace windbreeze
{
    class Camera
    {
        public:
            Camera(float x, float y, float width, float height);
            Camera(glm::vec2 position, glm::vec2 size);
            void setPosition(float x, float y);
            void setPosition(glm::vec2 p);
            const glm::vec2& getPosition();
            void translate(float x, float y);
            void translate(glm::vec2 p);
            void setSize(float x, float y);
            void setSize(glm::vec2 s);
            const glm::vec2& getSize();
            void setRotation(float radians);
            void rotate(float radians);
            glm::mat2x2 getTransformation();
            glm::vec2 transformPoint(const glm::vec2 point);
        private:
            glm::vec2 position;
            glm::vec2 size;
            float rotation = 0.0f;
    };
}
