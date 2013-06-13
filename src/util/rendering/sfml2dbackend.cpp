#include <framework/util/rendering/sfml2dbackend.h>
#include <iostream>

namespace windbreeze
{
    void Sfml2DBackend::setup()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glLoadIdentity();
        //gluOrtho2D(x, x + w, y + h, y);
        gluOrtho2D(0.0f, 1366.0f, 768.0f, 0.0f);

        std::cout << "setup the backend now\n";
    }

    void Sfml2DBackend::destroy()
    {
    }

    void Sfml2DBackend::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Sfml2DBackend::render(RenderData renderData)
    {
        std::vector<float> vertices = renderData.vertices;
        glm::vec2 vertex;
        glm::vec2 halfViewSize = viewSize * 0.5f;

        glBegin(GL_QUADS);
        for(uint32_t i = 0; i < vertices.size(); i += 2)
        {
            vertex = glm::vec2(vertices[i], vertices[i + 1]);
            vertex = (glm::inverse(cameraTransform) * (vertex - halfViewSize) + halfViewSize) - cameraPosition;
            glVertex2f(vertex.x, vertex.y);
        }
        glEnd();
    }
}
