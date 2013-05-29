#include <string>
#include <map>
#include <framework/application/gamestate.h>

namespace windstorm
{
    using StateName = std::string;

    class GameStateMachine
    {
        public:
            void addGameState(const std::string& name, std::shared_ptr<GameState> state);
            void setCurrentState(const std::string& name);
            bool isFinished();
            void run();
            ~GameStateMachine();
        private:
            void switchState(const std::string& nextName);
            std::weak_ptr<GameState> currentState;
            std::string currentStateName = "";
            std::map<StateName, std::shared_ptr<GameState> > gameStates;
    };
}
