#pragma once
#include <framework/rendering/camera.h>
#include <SFML/OpenGL.hpp>  //temp for testing

namespace windbreeze
{
    class Drawable2D;

    class Renderer2D
    {
        public:
            Renderer2D();
            void doStuff();
            void clear();
            void render(const Drawable2D& drawable);
            void setCamera(const Camera& camera);
        private:
            Camera currentCamera;
    };
}
