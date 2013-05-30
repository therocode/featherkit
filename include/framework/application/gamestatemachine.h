#include <string>
#include <map>
#include <stdexcept>
#include <framework/application/gamestate.h>

namespace windstorm
{
    using StateName = std::string;

    class GameStateException: public std::runtime_error
    {
        public:
            GameStateException():runtime_error("Game state not found"){}
            GameStateException(std::string msg):runtime_error(msg.c_str()){}
    };

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
