#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    class Quad : public Drawable2D
    {
        public:
            Quad();
            Quad(float w, float h);
            void setSize(float w, float h);
            void setSize(glm::vec2 size);
            glm::vec2 getSize();
    };
}
