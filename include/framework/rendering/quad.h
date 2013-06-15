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
            glm::vec2 getSize() const;
            void setTexture(const std::string& tex);
            const std::string& getTexture() const;
            virtual void getRenderData(RenderData& renderData) const override;
        protected:
            std::string textureId;
    };
}
