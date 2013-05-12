#include <string>
#include <map>
#include "gamestate.h"

namespace windstorm
{
    using StateName = std::string;

    class GameStateMachine
    {
        public:
            void addGameState(const std::string& name, GameState* state);
            void setCurrentState(const std::string& name);
            bool isFinished();
            void run();
            ~GameStateMachine();
        private:
            void switchState(const std::string& nextName);
            GameState* currentState = nullptr;
            std::string currentStateName = "";
            std::map<StateName, GameState*> gameStates;
    };
}
