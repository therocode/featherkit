#pragma once
#include <featherkit/rendering/quad.h>

namespace fk
{
    class SubrectQuad : public Quad
    {
        public:
            SubrectQuad();
            SubrectQuad(float w, float h);
            void setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
        private:
            glm::vec2 subrectStart;
            glm::vec2 subrectEnd;
    };
}
