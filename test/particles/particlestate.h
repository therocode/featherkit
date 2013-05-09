#include <gamestate.h>
#include <string>
#include <vector>
#include <entity/entitygroup.h>
#include "component.h"

enum {ORANGE, LIME, TURQUOISE, SKYBLUE, PURPLE, PINK};

void colourSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
void floatVec2Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);


class ParticleState : public windstorm::GameState
{
    public:
        ParticleState(sf::Window& sfw) : sfWindow(sfw){}
        void activate() override;
        void deactivate() override;
        void setup() override;
        std::string run() override;
        void destroy() override;
        ~ParticleState() override;
    private:
        void createQuark(int x, int y, float r, float g, float b);
        void createSpawner(int x, int y, float r, float g, float b);

        sf::Window& sfWindow;

        windgale::EntityFileLoader loader;
        windgale::BasicEntityBackend allData;
        windgale::EntityManager entityManager = allData;
        windgale::EntityGroup spawners;
        windgale::EntityGroup particles;
        windgale::EntityGroup all;

        SpawningComponent spawn = {&spawners, &entityManager};
        RenderComponent renderer = &sfWindow;
        PhysicsComponent physics;
        DeathComponent death = &entityManager;

        FloatVec2 colourPoints[6];

        int total = 0;
        int consecutiveSlowFrames = 0;
        int count = 0;
        bool paused = false;
};
