#pragma once
#include <featherkit/rendering/quad.h>

namespace fea
{
    class SubrectQuad : public Quad
    {
        public:
            SubrectQuad();
            SubrectQuad(float w, float h);
            SubrectQuad(const glm::vec2& size);
            void setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd);
            void setSubrect(float startX, float startY, float endX, float endY);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
        private:
            glm::vec2 subrectStart;
            glm::vec2 subrectEnd;
    };
}
