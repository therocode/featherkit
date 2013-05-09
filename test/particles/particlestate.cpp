#include "particlestate.h"

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

void ParticleState::activate()
{
}

void ParticleState::deactivate()
{
}

void ParticleState::setup()
{
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

    actionHandler.bindKeyPress(windbreeze::Keyboard::A, "bajsa");
    actionHandler.bindKeyRelease(windbreeze::Keyboard::A, "sluta bajsa");
    actionHandler.bindMousePress(windbreeze::Mouse::RIGHT, "kissa");
    actionHandler.bindMouseRelease(windbreeze::Mouse::RIGHT, "sluta kissa");
    actionHandler.bindGamepadPress(0, 0, "spy");
    actionHandler.bindGamepadRelease(0, 0, "sluta spy");
    actionHandler.bindGamepadPress(1, 0, "spotta");
    actionHandler.bindGamepadRelease(1, 0, "sluta spotta");

    inputHandler.setKeyRepeatEnabled(false);
}

std::string ParticleState::run()
{
    windbreeze::Event event;

    inputHandler.processEvents();
    actionHandler.processActions(inputHandler);
    while(inputHandler.pollEvent(event))
    {
        if(event.type == windbreeze::Event::CLOSED)
            shutDown = true;
        else if(event.type == windbreeze::Event::KEYPRESSED)
        {
            // quitting and stuff. add pause and restart herevent.
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
                shutDown = true;
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
                colourPoints[ORANGE] = {(float)inputHandler.getMouseGlobalPosition().x, (float)inputHandler.getMouseGlobalPosition().y}; 
            }
            else if(event.key.code == windbreeze::Keyboard::X)
            {
                colourPoints[LIME] = {(float)inputHandler.getMouseWindowPosition().x, (float)inputHandler.getMouseWindowPosition().y}; 
            }
            else if(event.key.code == windbreeze::Keyboard::C)
            {
                colourPoints[TURQUOISE] = {(float)inputHandler.getMouseWindowPosition().x, (float)inputHandler.getMouseWindowPosition().y}; 
            }
            else if(event.key.code == windbreeze::Keyboard::V)
            {
                colourPoints[SKYBLUE] = {(float)inputHandler.getMouseWindowPosition().x, (float)inputHandler.getMouseWindowPosition().y}; 
            }
            else if(event.key.code == windbreeze::Keyboard::B)
            {
                colourPoints[PURPLE] = {(float)inputHandler.getMouseWindowPosition().x, (float)inputHandler.getMouseWindowPosition().y}; 
            }
            else if(event.key.code == windbreeze::Keyboard::N)
            {
                colourPoints[PINK] = {(float)inputHandler.getMouseWindowPosition().x, (float)inputHandler.getMouseWindowPosition().y}; 
                inputHandler.setMouseGlobalPosition(100, 100);
            }
            else if(event.key.code == windbreeze::Keyboard::M)
            {
                spawn.add = !spawn.add;
                inputHandler.setMouseWindowPosition(100, 100);
            }
        }
        else if(event.type == windbreeze::Event::MOUSEBUTTONPRESSED)
        {
            float r = (float)(rand() % 256) / 255.0f;
            float g = (float)(rand() % 256) / 255.0f;
            float b = (float)(rand() % 256) / 255.0f;

            if(event.mouseButton.button == windbreeze::Mouse::LEFT)
            {
                for(int i = 0; i < 1000; i++)
                {
                    createQuark(event.mouseButton.x, event.mouseButton.y, r, g, b);
                }
            }
            else if(event.mouseButton.button == windbreeze::Mouse::RIGHT)
            {
                createSpawner(event.mouseButton.x, event.mouseButton.y, r, g, b);
            }
            else if(event.mouseButton.button == windbreeze::Mouse::MIDDLE)
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
        else if(event.type == windbreeze::Event::MOUSEMOVED)
        {
            float r = (float)(rand() % 256) / 255.0f;
            float g = (float)(rand() % 256) / 255.0f;
            float b = (float)(rand() % 256) / 255.0f;

            createQuark(event.mouseMove.x, event.mouseMove.y, r, g, b);
        }
        else if(event.type == windbreeze::Event::GAMEPADBUTTONPRESSED)
        {
            std::cout << "pressed button " << event.gamepadButton.button << " on gamepad " << event.gamepadButton.gamepadId << "\n";
        }
    }

    std::string action;
    while(actionHandler.pollAction(action))
    {
        std::cout << "this action happened: " << action << "\n";
    }

    sf::Clock clock;
    if(!paused)
    {
        particles.removeInvalid();
        physics.update(particles);
        spawn.update(colourPoints, particles);
        death.update(particles);
    }

    //if(inputHandler.isGamepadConnected(0))
    //{
    //    std::cout << "gamepad connected!\n";
    //    std::cout << "button amount " << inputHandler.getGamepadButtonCount(0) << "\n";
    //    if(inputHandler.gamepadHasAxis(0, windbreeze::Gamepad::X))
    //        std::cout << "it has axis x!\n";
    //    if(inputHandler.isGamepadButtonPressed(0, 5))
    //        std::cout << "now button 5 is pressed\n";
    //    std::cout << "position of axis y is " << inputHandler.getGamepadAxisPosition(0, windbreeze::Gamepad::Y) << "\n";
    //}

    if(inputHandler.isKeyPressed(windbreeze::Keyboard::G))
        std::cout << "G is pressed!\n";

    all = particles + spawners;
    all.removeInvalid();
    renderer.render(all);

    int frameCount = clock.getElapsedTime().asMilliseconds();

    if(frameCount > 18)
        consecutiveSlowFrames++;
    else
        consecutiveSlowFrames = 0;
    return "";
}

void ParticleState::destroy()
{
}

ParticleState::~ParticleState()
{
}

void ParticleState::createQuark(int x, int y, float r, float g, float b)
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

void ParticleState::createSpawner(int x, int y, float r, float g, float b)
{
    windgale::WeakEntityPtr spawner = entityManager.createEntity("spawner");

    windgale::EntityPtr locked = spawner.lock();
    locked->setAttribute<Colour>("currentcolour", {r, g, b});
    locked->setAttribute<FloatVec2>("position", {(float)x, (float)y});

    spawners.add(spawner);

    count++;
}
