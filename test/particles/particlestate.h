#include <GameState.h>

class ParticleState : public Gamestate
{
    public:
        void setup() override;
        void run() override;
        void destroy() override;
};
