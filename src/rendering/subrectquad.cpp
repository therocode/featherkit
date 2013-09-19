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
        setSubrect(glm::vec2(xStart, yStart), glm::vec2(xEnd, yEnd));
    }

    void SubrectQuad::setSubrect(const glm::vec2& srStart, const glm::vec2& srEnd)
    {
        subrectStart = srStart;
        subrectEnd = srEnd;

        glm::vec2 texCoordsX = glm::vec2(subrectStart.x, subrectEnd.x) * hFlip;
        glm::vec2 texCoordsY = glm::vec2(subrectStart.y, subrectEnd.y) * vFlip;

        texCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};
    }

    RenderInfo SubrectQuad::getRenderInfo() const
    {
        RenderInfo temp = Quad::getRenderInfo();
        std::hash<std::string> stringHasher;

        temp.vertexAttributes.push_back(VertexAttribute(stringHasher("texCoords"), &texCoords[0]));

        return temp;
    }
}
