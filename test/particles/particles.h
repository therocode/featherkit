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
#include <iostream>
#include <cstring>

enum {ORANGE, LIME, TURQUOISE, SKYBLUE, PURPLE, PINK};

void colourSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
void floatVec2Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);

class Particles : public windstorm::Application
{
    public:
        void setup() override;
        void run() override;
        void destroy() override; 
    private:
        void createQuark(int x, int y, float r, float g, float b);
        void createSpawner(int x, int y, float r, float g, float b);

        sf::Window window;
        windbreeze::Window windbreezeow;

        windbreeze::SFMLInputBackend sfmlBackend = window;
        windbreeze::InputHandler inputHandler = sfmlBackend;
        windbreeze::ActionHandler<std::string> actionHandler;

        windgale::EntityFileLoader loader;
        windgale::BasicEntityBackend allData;
        windgale::EntityManager entityManager = allData;
        windgale::EntityGroup spawners;
        windgale::EntityGroup particles;
        windgale::EntityGroup all;

        SpawningComponent spawn = {&spawners, &entityManager};
        RenderComponent renderer = &window;
        PhysicsComponent physics;
        DeathComponent death = &entityManager;

        FloatVec2 colourPoints[6];

        int total = 0;
        int consecutiveSlowFrames = 0;
        int count = 0;
        bool paused = false;

};
