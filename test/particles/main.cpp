#include <entitybackends/basicentitybackend.h>
#include <util/defaultsetters.h>
#include <entity/entitygroup.h>
#include <util/entityfileloader.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "component.h"
#include <iostream>
#include <cstring>
#include <sfmleventbackend.h>

windgale::BasicEntityBackend allData;
sf::Window window;
windbreeze::SFMLEventBackend sfmlEventBackend(window);
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

    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            running = false;
        if(event.type == sf::Event::KeyPressed)
        {
            // quitting and stuff. add pause and restart here.
            if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Escape)
                running = false;
            // pause
            else if (event.key.code == sf::Keyboard::P)
                paused = !paused;
            else if (event.key.code == sf::Keyboard::R)
            {
                entityManager.removeEntities(spawners);
                spawners.remove(spawners);
                all = particles;
            }
            else if(event.key.code == sf::Keyboard::E)
            {
                entityManager.removeEntities(entityManager.getAll() - spawners);
                particles.clear();
                all = spawners;
            }
            else if(event.key.code == sf::Keyboard::T)
            {
                entityManager.removeAll();
                spawners.clear();
                all.clear();
                particles.clear();
            }
            else if(event.key.code == sf::Keyboard::Y)
            {
                entityManager.reset();
                spawners.clear();
                all.clear();
                particles.clear();
            }
            else if(event.key.code == sf::Keyboard::Z)
            {
               colourPoints[ORANGE] = {(float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y}; 
            }
            else if(event.key.code == sf::Keyboard::X)
            {
               colourPoints[LIME] = {(float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y}; 
            }
            else if(event.key.code == sf::Keyboard::C)
            {
               colourPoints[TURQUOISE] = {(float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y}; 
            }
            else if(event.key.code == sf::Keyboard::V)
            {
               colourPoints[SKYBLUE] = {(float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y}; 
            }
            else if(event.key.code == sf::Keyboard::B)
            {
               colourPoints[PURPLE] = {(float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y}; 
            }
            else if(event.key.code == sf::Keyboard::N)
            {
               colourPoints[PINK] = {(float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y}; 
            }
            else if(event.key.code == sf::Keyboard::M)
            {
               spawn.add = !spawn.add;
            }
        }
        if(event.type == sf::Event::MouseButtonPressed)
        {
            float r = (float)(rand() % 256) / 255.0f;
            float g = (float)(rand() % 256) / 255.0f;
            float b = (float)(rand() % 256) / 255.0f;
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for(int i = 0; i < 1000; i++)
                {
                    createQuark(event.mouseButton.x, event.mouseButton.y, r, g, b);
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                createSpawner(event.mouseButton.x, event.mouseButton.y, r, g, b);
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                for(int i = 0; i < 50; i++)
                {
                    float rs = (float)(rand() % 256) / 255.0f;
                    float gs = (float)(rand() % 256) / 255.0f;
                    float bs = (float)(rand() % 256) / 255.0f;
                    createSpawner(event.mouseButton.x + (rand() % 50 - 25), event.mouseButton.y + (rand() % 50 - 25), rs, gs, bs);
                }
            }
        }
        if(event.type == sf::Event::MouseMoved)
        {
            float r = (float)(rand() % 256) / 255.0f;
            float g = (float)(rand() % 256) / 255.0f;
            float b = (float)(rand() % 256) / 255.0f;
            
            createQuark(event.mouseMove.x, event.mouseMove.y, r, g, b);
        }
    }

    sf::Clock clock;
    if(!paused)
    {
        particles.removeInvalid();
        physics.update(particles);
        //spawn.update(colourPoints, particles);
        //death.update(particles);
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
