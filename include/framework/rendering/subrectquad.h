#pragma once
#include <framework/rendering/quad.h>

namespace windbreeze
{
    class SubrectQuad : public Quad
    {
        public:
            SubrectQuad() : Quad() {}
            SubrectQuad(float w, float h) : Quad(w, h) {}
            void setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
        private:
            glm::vec2 subrectStart;
            glm::vec2 subrectEnd;
    };
}
