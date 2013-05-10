#include "particles.h"

void Particles::setup()
{
    window.create(windbreeze::VideoMode(1366, 768), "Particles");
    window.setFramerateLimit(60);

    stateMachine.addGameState("particles", new ParticleState(sfWindow, inputHandler, actionHandler));
    stateMachine.setState("particles");
}

void Particles::run()
{
    while(!shutDown)
    {
        stateMachine.run();
    }
}

void Particles::destroy()
{
    window.close();
}
