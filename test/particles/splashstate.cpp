#include "splashstate.h"
#include <iostream>

void SplashState::setup()
{
    splashTexture.loadFromFile("test/particles/splash.png");
    splashSprite.setTexture(splashTexture);
    splashSprite.setPosition(0, 0);
}

std::string SplashState::run()
{
    windbreeze::Event event;
    std::string nextState;

    inputHandler.processEvents();

    while(inputHandler.pollEvent(event))
    {
        if(event.type == windbreeze::Event::CLOSED)
            nextState = "NONE";
        else if(event.type == windbreeze::Event::KEYPRESSED)
        {
            // quitting and stuff. add pause and restart herevent.
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
                nextState = "NONE";
            else if (event.key.code == windbreeze::Keyboard::SPACE || event.key.code == windbreeze::Keyboard::RETURN)
                nextState = "particles";
        }
        else if(event.type == windbreeze::Event::RESIZED)
        {
            std::cout << event.size.width << "\n";
            splashSprite.setScale(event.size.width, event.size.height);
            splashSprite.setPosition(0, 0);
        }
    }

    sfWindow.clear();
    sfWindow.draw(splashSprite);
    sfWindow.display();

    return nextState;
}
