#pragma once
#include <framework/rendering/camera.h>
#include <framework/rendering/renderer2dbackend.h>

namespace windbreeze
{
    class Drawable2D;

    class Renderer2D
    {
        public:
            Renderer2D(Renderer2DBackend& b, glm::vec2 s, Camera c);
            void setup();
            void destroy();
            void clear();
            void preRender();
            void render(const Drawable2D& drawable);
            void postRender();
            void setCamera(const Camera& camera);
            Camera& getCamera();
        private:
            Renderer2DBackend& backend;
            glm::vec2 renderSize;
            Camera currentCamera;
    };
}
