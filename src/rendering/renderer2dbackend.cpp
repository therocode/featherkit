#include <framework/rendering/renderer2dbackend.h>

namespace windbreeze
{
    void Renderer2DBackend::setCameraPosition(glm::vec2 position)
    {
        cameraPosition = position;
    }
            
    void Renderer2DBackend::setCameraTransform(glm::mat2x2 transform)
    {
        cameraTransform = transform; 
    }
    
    void Renderer2DBackend::setViewSize(glm::vec2 size)
    {
        viewSize = size;
    }
}
