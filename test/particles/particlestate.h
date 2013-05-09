#include <gamestate.h>

enum {ORANGE, LIME, TURQUOISE, SKYBLUE, PURPLE, PINK};

void colourSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
void floatVec2Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);


class ParticleState : public windstorm::GameState
{
    public:
        void setup() override;
        void run() override;
        void destroy() override;
};
