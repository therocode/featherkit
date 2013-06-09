#include <framework/glm/glm.hpp>

namespace windbreeze
{
    class Camera
    {
        public:
            void setPosition(float x, float y);
            void setPosition(glm::vec2 p);
            void setRotation(float radians);
            glm::vec2 getTranslation();
            glm::mat2x2 getTransformation();
        private:
            glm::vec2 position;
            float rotation = 0.0f;
    };
}
