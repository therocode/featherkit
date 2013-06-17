#pragma once
#include <framework/rendering/animatedquad.h>

namespace windbreeze
{
    class RepeatedQuad : public AnimatedQuad
    {
        public:
            RepeatedQuad() : AnimatedQuad() {tileSize = getSize();}
            RepeatedQuad(float w, float h) : AnimatedQuad(w, h) {tileSize = getSize();}
            void setTileSize(glm::vec2 size);
            const glm::vec2& getTileSize();
            void setScrollSpeed(glm::vec2 speed);
            const glm::vec2& getScrollSpeed() const;
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
        protected:
            glm::vec2 tileSize;
            glm::vec2 scrollSpeed;
            glm::vec2 currentScroll;
    };
}
