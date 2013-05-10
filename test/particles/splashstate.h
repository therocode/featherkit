#include <gamestate.h>
#include <vector>
#include <inputhandler.h>
#include <SFML/Graphics.hpp>

class SplashState : public windstorm::GameState
{
    public:
        SplashState(sf::Window& sfw, windbreeze::InputHandler& ih) : sfWindow((sf::RenderWindow&)sfw), inputHandler(ih) {}
        void setup() override;
        std::string run() override;
    private:
        sf::RenderWindow& sfWindow;
        windbreeze::InputHandler& inputHandler;
        sf::Texture splashTexture;
        sf::Sprite splashSprite;
};
