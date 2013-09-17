#include <featherkit/rendering/subrectquad.h>

namespace fea
{
    SubrectQuad::SubrectQuad() : Quad(), subrectEnd(1.0f, 1.0f)
    {
    }

    SubrectQuad::SubrectQuad(float w, float h) : Quad(w, h), subrectEnd(1.0f, 1.0f)
    {
    }

    SubrectQuad::SubrectQuad(const glm::vec2& size) : Quad(size), subrectEnd(1.0f, 1.0f)
    {
    }

    void SubrectQuad::setSubrect(float xStart, float yStart, float xEnd, float yEnd)
    {
        subrectStart = glm::vec2(xStart, yStart);
        subrectEnd = glm::vec2(xEnd, yEnd);
    }

    void SubrectQuad::setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd)
    {
        subrectStart = srStart;
        subrectEnd = srEnd;
    }
}
