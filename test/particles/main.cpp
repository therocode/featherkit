#include <entitybackends/basicentitybackend.h>
#include <util/defaultsetters.h>
#include <entity/entitygroup.h>
#include <util/entityfileloader.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "component.h"
#include <iostream>
#include <cstring>
#include <eventhandler.h>
#include <sfmleventbackend.h>

windgale::BasicEntityBackend allData;
sf::Window window;
windbreeze::SFMLEventBackend sfmlBackend(window);
windbreeze::EventHandler eventHandler(sfmlBackend);
windgale::EntityFileLoader loader;
windgale::EntityManager entityManager(allData);
windgale::EntityGroup spawners;
windgale::EntityGroup particles;
windgale::EntityGroup all;
SpawningComponent spawn(&spawners, &entityManager);
RenderComponent renderer(&window);
PhysicsComponent physics;
DeathComponent death(&entityManager);

FloatVec2 colourPoints[6];
enum { ORANGE, LIME, TURQUOISE, SKYBLUE, PURPLE, PINK};

int total = 0;
int consecutiveSlowFrames = 0;
int count = 0;
bool paused = false;

void colourSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
{
    Colour col;
    col.r = std::stof(arguments[0]);
    col.g = std::stof(arguments[1]);
    col.b = std::stof(arguments[2]);

    entity.lock()->setAttribute<Colour>(attribute, col);
}

void floatVec2Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
{
    FloatVec2 val;

    val.x = std::stoi(arguments[0]);
    val.y = std::stoi(arguments[1]);

    entity.lock()->setAttribute<FloatVec2>(attribute, val);
}

void createQuark(int x, int y, float r, float g, float b)
{
    windgale::WeakEntityPtr particle = entityManager.createEntity("particle");

    FloatVec2 velocity;
    velocity.x = (rand() % 100 - 50) * 0.5f;
    velocity.y = (rand() % 100 - 50) * 0.5f;

    windgale::EntityPtr locked = particle.lock();
    locked->setAttribute<Colour>("currentcolour", {r, g, b});
    locked->setAttribute<FloatVec2>("position", {(float)x, (float)y});
    locked->setAttribute<FloatVec2>("velocity", velocity);
    particles.add(particle);
    count += 1;
}

void createSpawner(int x, int y, float r, float g, float b)
{
    windgale::WeakEntityPtr spawner = entityManager.createEntity("spawner");

    windgale::EntityPtr locked = spawner.lock();
    locked->setAttribute<Colour>("currentcolour", {r, g, b});
    locked->setAttribute<FloatVec2>("position", {(float)x, (float)y});

    spawners.add(spawner);

    count++;
}

void setup()
{
    window.create(sf::VideoMode(1366, 768), "Particles");
    window.setFramerateLimit(60);

    renderer.setup();

    entityManager.registerAttributes(loader.loadAttributesJson("test/particles/attributes.json"));
    entityManager.registerEntityTypes(loader.loadEntitiesJson("test/particles/entities.json"));

    entityManager.setDefaultSetter("currentcolour", &colourSetter);
    entityManager.setDefaultSetter("position", &floatVec2Setter);
    entityManager.setDefaultSetter("velocity", &floatVec2Setter);
    entityManager.setDefaultSetter("spawnrate", &windgale::uint32Setter);
    entityManager.setDefaultSetter("spawnpower", &windgale::floatSetter);
    entityManager.setDefaultSetter("deathrate", &windgale::uint32Setter);
    entityManager.setDefaultSetter("id", &windgale::idSetter);
}

int run()
{
    bool running = true;

    windbreeze::Event event;

    eventHandler.processEvents();
    while(eventHandler.pollEvent(event))
    {
        if(event.type == windbreeze::Event::CLOSED)
            running = false;
        else if(event.type == windbreeze::Event::RESIZED)
            std::cout << "resized\n";
        else if(event.type == windbreeze::Event::LOSTFOCUS)
            std::cout << "lost focus\n";
        else if(event.type == windbreeze::Event::GAINEDFOCUS)
            std::cout << "gained focus\n";
        else if(event.type == windbreeze::Event::KEYPRESSED)
        {
            // quitting and stuff. add pause and restart herevent.
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
                running = false;
            // pause
            else if (event.key.code == windbreeze::Keyboard::P)
                paused = !paused;
            else if (event.key.code == windbreeze::Keyboard::R)
            {
                entityManager.removeEntities(spawners);
                spawners.remove(spawners);
                all = particles;
            }
            else if(event.key.code == windbreeze::Keyboard::E)
            {
                entityManager.removeEntities(entityManager.getAll() - spawners);
                particles.clear();
                all = spawners;
            }
            else if(event.key.code == windbreeze::Keyboard::T)
            {
                entityManager.removeAll();
                spawners.clear();
                all.clear();
                particles.clear();
            }
            else if(event.key.code == windbreeze::Keyboard::Y)
            {
                entityManager.reset();
                spawners.clear();
                all.clear();
                particles.clear();
            }
            else if(event.key.code == windbreeze::Keyboard::Z)
            {
               //colourPoints[ORANGE] = {(float)windbreeze::Mouse::getPosition().x, (float)windbreeze::Mouse::getPosition().y}; 
               colourPoints[ORANGE] = {(float)200.0f, (float)200.0f}; 
            }
            else if(event.key.code == windbreeze::Keyboard::X)
            {
               colourPoints[LIME] = {200.0f, 200.0f}; 
            }
            else if(event.key.code == windbreeze::Keyboard::C)
            {
               colourPoints[TURQUOISE] = {200.0f, 200.0f}; 
            }
            else if(event.key.code == windbreeze::Keyboard::V)
            {
               colourPoints[SKYBLUE] = {200.0f, 200.0f}; 
            }
            else if(event.key.code == windbreeze::Keyboard::B)
            {
               colourPoints[PURPLE] = {200.0f, 200.0f}; 
            }
            else if(event.key.code == windbreeze::Keyboard::N)
            {
               colourPoints[PINK] = {200.0f, 200.0f}; 
            }
            else if(event.key.code == windbreeze::Keyboard::M)
            {
               spawn.add = !spawn.add;
            }
        }
    }

    //while (window.pollEvent(event))
    //{
    //    if(event.type == sf::Event::MouseButtonPressed)
    //    {
    //        float r = (float)(rand() % 256) / 255.0f;
    //        float g = (float)(rand() % 256) / 255.0f;
    //        float b = (float)(rand() % 256) / 255.0f;
    //        
    //        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //        {
    //            for(int i = 0; i < 1000; i++)
    //            {
    //                createQuark(event.mouseButton.x, event.mouseButton.y, r, g, b);
    //            }
    //        }
    //        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    //        {
    //            createSpawner(event.mouseButton.x, event.mouseButton.y, r, g, b);
    //        }
    //        else if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    //        {
    //            for(int i = 0; i < 50; i++)
    //            {
    //                float rs = (float)(rand() % 256) / 255.0f;
    //                float gs = (float)(rand() % 256) / 255.0f;
    //                float bs = (float)(rand() % 256) / 255.0f;
    //                createSpawner(event.mouseButton.x + (rand() % 50 - 25), event.mouseButton.y + (rand() % 50 - 25), rs, gs, bs);
    //            }
    //        }
    //    }
    //    if(event.type == sf::Event::MouseMoved)
    //    {
    //        float r = (float)(rand() % 256) / 255.0f;
    //        float g = (float)(rand() % 256) / 255.0f;
    //        float b = (float)(rand() % 256) / 255.0f;
    //        
    //        createQuark(event.mouseMove.x, event.mouseMove.y, r, g, b);
    //    }
    //}

    sf::Clock clock;
    if(!paused)
    {
        particles.removeInvalid();
        physics.update(particles);
        spawn.update(colourPoints, particles);
        death.update(particles);
    }

    all = particles + spawners;
    all.removeInvalid();
    renderer.render(all);

    int frameCount = clock.getElapsedTime().asMilliseconds();

    if(frameCount > 18)
        consecutiveSlowFrames++;
    else
        consecutiveSlowFrames = 0;

    //if(consecutiveSlowFrames > 100)
    //    exit(0);

    return running;
}

void shutDown()
{
    window.close();
}

int main()
{

    setup();
    while(run());
    shutDown();
}
