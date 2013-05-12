#include <gamestate.h>
#include <vector>
#include <inputhandler.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class SplashState : public windstorm::GameState
{
    public:
        SplashState(sf::Window& sfw, windbreeze::InputHandler& ih) : sfWindow(sfw), inputHandler(ih) {}
        void setup() override;
        std::string run() override;
    private:
        sf::Window& sfWindow;
        windbreeze::InputHandler& inputHandler;
        sf::Image splashImage;
        GLuint texture;
};
