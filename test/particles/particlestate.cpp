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
}

std::string ParticleState::run()
{
    return "";
}

void ParticleState::destroy()
{
}

ParticleState::~ParticleState()
{
}
