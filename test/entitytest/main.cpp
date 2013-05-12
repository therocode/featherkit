#include "gale/entitymanager.h"
#include "gale/entityfileloader.h"
#include "gale/entity.h"
#include "gale/basicentitybackend.h"
#include <iostream>

struct FloatVec2
{
    float x;
    float y;
};

void floatSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
{
    float val = std::stof(arguments[0]);

    entity.lock()->setAttribute(attribute, val);
}

void floatVec2Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
{
    FloatVec2 val;

    val.x = std::stoi(arguments[0]);
    val.y = std::stoi(arguments[1]);

    entity.lock()->setAttribute(attribute, val);
}

int main()
{
    windgale::BasicEntityBackend dataManager;
    windgale::EntityFileLoader loader;
    windgale::EntityManager entityManager(dataManager);

    entityManager.registerAttributes(loader.loadAttributesJson("test/entitytest/attributes.json"));
    entityManager.registerEntityTypes(loader.loadEntitiesJson("test/entitytest/entities.json"));

    entityManager.setDefaultSetter("mass", &floatSetter);
    entityManager.setDefaultSetter("position", &floatVec2Setter);
    entityManager.setDefaultSetter("velocity", &floatVec2Setter);

    windgale::WeakEntityPtr particle = entityManager.createEntity("particle");
    windgale::WeakEntityPtr staticParticle = entityManager.createEntity("staticparticle");

    float mass = particle.lock()->getAttribute<float>("mass");
    std::cout << "entity particle had mass " << mass << "\n";
}
