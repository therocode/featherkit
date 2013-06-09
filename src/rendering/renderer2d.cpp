#include <framework/glm/glm.hpp>
#include <framework/rendering/renderer2d.h>
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    Renderer2D::Renderer2D() : currentCamera(1366.0f * 0.5f, 768.0f * 0.5f, 1366.0f, 768.0f)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    void Renderer2D::doStuff()
    {
        glm::vec2 hej(45.0f, 10.0f);
        glm::vec2 hoj(35.0f, 5.0f);

        float angle = glm::radians(90.0f);
        glm::mat2x2 rot(glm::cos(angle), glm::sin(angle), -glm::sin(angle), glm::cos(angle));

        hej = hej + hoj;

        hej = rot * hej;
    }
            
    void Renderer2D::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        float camX = currentCamera.getPosition().x;
        float camY = currentCamera.getPosition().y;
        float camWidth = currentCamera.getSize().x;
        float camHeight = currentCamera.getSize().y;

        gluOrtho2D(camX, camX + camWidth, camY + camHeight, camY);
    }

    void Renderer2D::render(const Drawable2D& drawable)
    {
        const std::vector<float>& vertices = drawable.getVerticesTransformed();

        glm::vec2 vertex;
        glm::vec2 halfCameraSize = currentCamera.getSize() * 0.5f;

        glBegin(GL_QUADS);
        for(uint32_t i = 0; i < vertices.size(); i += 2)
        {
            vertex = glm::vec2(vertices[i], vertices[i + 1]);
            vertex = (currentCamera.getTransformation()) * (vertex + currentCamera.getTranslation() - halfCameraSize) + halfCameraSize;
            glVertex2f(vertex.x, vertex.y);
        }
        glEnd();

    }

    void Renderer2D::setCamera(const Camera& camera)
    {
        currentCamera = camera;
    }
    
    Camera& Renderer2D::getCamera()
    {
        return currentCamera;
    }
}
