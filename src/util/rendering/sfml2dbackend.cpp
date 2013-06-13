#include <framework/util/rendering/sfml2dbackend.h>

namespace windbreeze
{
    void Sfml2DBackend::setup()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    void Sfml2DBackend::destroy()
    {
    }

    void Sfml2DBackend::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Sfml2DBackend::setViewRect(float x, float y, float w, float h)
    {
        glLoadIdentity();
        gluOrtho2D(x, x + w, y + h, y);

        viewSize = glm::vec2(w, h);
    }
            
    void Sfml2DBackend::setViewTransform(glm::mat2x2 transform)
    {
        viewTransform = transform; 
    }

    void Sfml2DBackend::render(RenderData renderData)
    {
        glBegin(GL_QUADS);
        for(uint32_t i = 0; i < vertices.size(); i += 2)
        {
            vertex = glm::vec2(vertices[i], vertices[i + 1]);
            vertex = (currentCamera.getTransformation()) * (vertex + currentCamera.getTranslation() - halfCameraSize) + halfCameraSize;
            glVertex2f(vertex.x, vertex.y);
        }
        glEnd();
    }
}
