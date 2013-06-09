#pragma once
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
        private:
            
    };
}
