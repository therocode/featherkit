#include <application.h>
#include <SFML/Graphics.hpp>
#include <inputhandler.h>
#include <sfmlinputbackend.h>
#include <actionhandler.h>
#include <util/entityfileloader.h>
#include <entitybackends/basicentitybackend.h>
#include <entity/entitygroup.h>
#include "component.h"
#include <util/defaultsetters.h>
#include <SFML/System/Clock.hpp>
#include <window.h>
#include <sfmlwindowbackend.h>
#include <iostream>
#include <cstring>
#include "particlestate.h"
#include <gamestatemachine.h>

class Particles : public windstorm::Application
{
    public:
        void setup() override;
        void run() override;
        void destroy() override; 
    private:
        windstorm::GameStateMachine stateMachine;

        sf::Window sfWindow;
        windbreeze::SFMLWindowBackend sfmlWindowBackend = sfWindow;
        windbreeze::Window window = sfmlWindowBackend;

        windbreeze::SFMLInputBackend sfmlInputBackend = sfWindow;
        windbreeze::InputHandler inputHandler = sfmlInputBackend;
        windbreeze::ActionHandler<std::string> actionHandler;
};
