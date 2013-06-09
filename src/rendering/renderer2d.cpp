#include <framework/rendering/renderer2d.h>
#include <framework/glm/glm.hpp>
#include <iostream>

namespace windbreeze
{
    void Renderer2D::doStuff()
    {
        glm::vec2 hej(45.0f, 10.0f);
        glm::vec2 hoj(35.0f, 5.0f);

        hej = hej + hoj;

        std::cout << "the vector is:\n  [" << hej[0] << ", " << hej[1] << "]\n";
    }
}
