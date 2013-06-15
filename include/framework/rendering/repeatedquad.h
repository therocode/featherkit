#pragma once
#include <framework/rendering/quad.h>

namespace windbreeze
{
    class RepeatedQuad : public Quad
    {
        public:
            RepeatedQuad() : Quad() {tileSize = getSize();}
            RepeatedQuad(float w, float h) : Quad(w, h) {tileSize = getSize();}
            void setTileSize(glm::vec2 size);
            const glm::vec2& getTileSize();
            virtual void getRenderData(RenderData& renderData) const override;
        protected:
            glm::vec2 tileSize;
    };
}
