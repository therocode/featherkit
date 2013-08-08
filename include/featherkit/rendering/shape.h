#pragma once
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/texture.h>

namespace fea
{
    class Shape : public Drawable2D
    {
        public:
            Shape();
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
            void setTexture(const Texture& tex);
            const Texture& getTexture() const;
            void setVertices(const std::vector<float>& vert, const std::vector<float>& tex);
        private:
            const Texture* texture;
            std::vector<float> texCoords;
    };
}
