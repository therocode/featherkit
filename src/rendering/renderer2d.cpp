#include <framework/glm/glm.hpp>
#include <framework/rendering/renderer2d.h>
#include <framework/rendering/drawable2d.h>
#include <iostream>

namespace windbreeze
{
    Renderer2D::Renderer2D()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        gluOrtho2D(0.0f, 1366.0f, 768.0f, 0.0f);
    }

    void Renderer2D::doStuff()
    {
        glm::vec2 hej(45.0f, 10.0f);
        glm::vec2 hoj(35.0f, 5.0f);

        float angle = glm::radians(90.0f);
        glm::mat2x2 rot(glm::cos(angle), glm::sin(angle), -glm::sin(angle), glm::cos(angle));

        hej = hej + hoj;

        std::cout << "the vector is:\n  [" << hej[0] << ", " << hej[1] << "]\n";
        hej = rot * hej;
        std::cout << "the vector is:\n  [" << hej[0] << ", " << hej[1] << "]\n";
    }
            
    void Renderer2D::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer2D::render(const Drawable2D& drawable)
    {
        const std::vector<float>& vertices = drawable.getVerticesTransformed();
        std::cout << "///////////////drawing the drawable!\nIt has " << vertices.size() << " vertices!\n";

        glm::vec2 vertex;

        glBegin(GL_QUADS);
        for(uint32_t i = 0; i < vertices.size(); i += 2)
        {
            vertex = glm::vec2(vertices[i], vertices[i + 1]);
            vertex = (currentCamera.getTransformation() * vertex) + currentCamera.getTranslation();
            std::cout << "drawing vertex nr " << i * 0.5 << "\n";
            std::cout << "x position: " << vertex.x << "\n";
            std::cout << "y position: " << vertex.y << "\n\n";
            glVertex2f(vertex.x, vertex.y);
        }
        glEnd();
        std::cout << "done drawing it!\n\n\n";

    }

    void Renderer2D::setCamera(const Camera& camera)
    {
        currentCamera = camera;
    }
}
