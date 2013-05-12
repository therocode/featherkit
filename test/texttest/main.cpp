#include <gale/basicentitybackend.h>
#include <gale/defaultsetters.h>
#include <gale/entitygroup.h>
#include <gale/entityfileloader.h>
#include <iostream>
#include <cstring>
#include <functional>

windgale::BasicEntityBackend allData;
windgale::EntityFileLoader loader;
windgale::EntityManager entityManager(allData);
windgale::EntityGroup spawners;

int main()
{
    std::hash<std::string> hasher;
    std::cout << "position : " << hasher("position") << "\n";
    std::cout << "velocity : " << hasher("velocity") << "\n";
    std::cout << "colour : " << hasher("colour") << "\n";
    std::cout << "speed : " << hasher("speed") << "\n";
    entityManager.registerAttributes(loader.loadAttributesJson("test/texttest/attributes.json"));
    entityManager.registerEntityTypes(loader.loadEntitiesJson("test/texttest/entities.json"));

    entityManager.createEntity("krok");

    entityManager.createEntity("krok");

    entityManager.createEntity("krok");


    entityManager.removeAll();

    entityManager.createEntity("krok");

    entityManager.createEntity("krok");

    entityManager.createEntity("slak");

    entityManager.createEntity("slak");

    entityManager.createEntity("krok");

    entityManager.createEntity("slak");

    std::cout << "HAJ\n";
    windgale::EntityId tjafs1 = entityManager.createEntity("tjafs").lock()->getId();
    std::cout << "HEJ\n";

    entityManager.createEntity("krok");

    entityManager.createEntity("slak");

    windgale::EntityId tjafs2 = entityManager.createEntity("tjafs").lock()->getId();

    entityManager.createEntity("krok");

    entityManager.removeEntity(tjafs1);
    entityManager.removeEntity(tjafs2);

    entityManager.removeEntity(8);
    entityManager.removeEntity(0);
    entityManager.removeEntity(3);
    entityManager.removeEntity(5);

    entityManager.removeEntity(4);
    entityManager.removeEntity(1);
    entityManager.removeEntity(7);
    entityManager.removeEntity(2);
    entityManager.removeEntity(10);


    entityManager.createEntity("krok");

    entityManager.createEntity("krok");

    entityManager.createEntity("krok");

    entityManager.removeAll();

    entityManager.createEntity("krok");

    entityManager.createEntity("krok");

    entityManager.createEntity("slak");

    entityManager.createEntity("slak");

    entityManager.createEntity("krok");

    entityManager.createEntity("slak");

    windgale::EntityId tjafs3 = entityManager.createEntity("tjafs").lock()->getId();

    entityManager.createEntity("krok");

    entityManager.createEntity("slak");

    windgale::EntityId tjafs4 = entityManager.createEntity("tjafs").lock()->getId();
    entityManager.createEntity("krok");
    entityManager.removeEntity(tjafs3);
    entityManager.removeEntity(tjafs4);

    entityManager.removeEntity(8);
    entityManager.removeEntity(2);
    entityManager.removeEntity(1);
    entityManager.removeEntity(5);

    entityManager.removeEntity(4);
    entityManager.removeEntity(0);
    entityManager.removeEntity(7);
    entityManager.removeEntity(6);
    entityManager.removeEntity(10);
}
