#include <SFML/Graphics.hpp>
#include <entity/entitygroup.h>

namespace windgale
{
    class BasicEntityBackend;
}

struct FloatVec2
{
    float x;
    float y;
};

struct Colour
{
    float r;
    float g;
    float b;
};

class RenderComponent
{
    public:
        RenderComponent(sf::Window* w) : window(w), highestEnergy(0.0f), positionBuffer(nullptr), colourBuffer(nullptr), currentSize(0){}
        void setup();
        void render(windgale::EntityGroup& all);
        ~RenderComponent();
    private:
        void extendBuffers(int newSize);
        sf::Window* window;
        float highestEnergy;
        float* positionBuffer;
        float* colourBuffer;
        uint32_t currentSize;
};

class PhysicsComponent
{
    public:
        PhysicsComponent() : gravityConstant(0.3987f){}
        void update(windgale::EntityGroup& p);
    private:
        float gravityConstant;
};

class SpawningComponent
{
    public:
        SpawningComponent(windgale::EntityGroup* s, windgale::EntityManager* e) : spawners(s), entityManager(e){}
        void update(FloatVec2 colourPoints[6], windgale::EntityGroup& particles);
        bool add = true;
    private:
        windgale::EntityGroup* spawners;
        windgale::EntityManager* entityManager;
};

class DeathComponent
{
    public:
        DeathComponent(windgale::EntityManager* e) : entityManager(e){}
        void update(windgale::EntityGroup& p);
    private:
        windgale::EntityManager* entityManager;
};
