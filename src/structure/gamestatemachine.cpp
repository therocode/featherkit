#include <framework/structure/gamestatemachine.h>
#include <sstream>

namespace windstorm
{
    void GameStateMachine::addGameState(const std::string& name, std::shared_ptr<GameState> state)
    {
        state->setup();
        gameStates.insert(std::pair<std::string, std::shared_ptr<GameState> >(name, state));
    }

    void GameStateMachine::setCurrentState(const std::string& name)
    {
        if(gameStates.find(name) != gameStates.end())
        {
            if(currentState.expired())
            {
                currentState = gameStates.at(name);
                currentState.lock()->activate("");
                currentStateName = name;
            }
            else
            {
                switchState(name);
            }
        }
        else
        {
            std::stringstream ss;
            ss << "Error! Game state " << name << " does not exist!\n";
            throw GameStateException(ss.str());
        }
    }
    
    bool GameStateMachine::isFinished() const
    {
        return currentState.expired();
    }

    GameStateMachine::~GameStateMachine()
    {
        for(auto statePair : gameStates)
        {
            statePair.second->destroy();
        }
    }

    void GameStateMachine::switchState(const std::string& nextStateName)
    {
        if(nextStateName == currentStateName)
        {
            return;
        }

        if(gameStates.find(nextStateName) != gameStates.end())
        {
            currentState.lock()->deactivate(nextStateName);

            std::weak_ptr<GameState> previousState = currentState;
            std::string previousStateName = currentStateName;

            currentState = gameStates.at(nextStateName);
            currentStateName = nextStateName;

            currentState.lock()->handOver(previousState, previousStateName);

            currentState.lock()->activate(previousStateName);
        }
        else
        {
            std::stringstream ss;
            ss << "Error! Game state " << nextStateName << " does not exist!\n";
            throw GameStateException(ss.str());
        }
    }
    
    void GameStateMachine::run()
    {
        if(currentStateName != "NONE")
        {
            std::string returned = currentState.lock()->run();
            if(returned != "")
            {
                if(returned == "NONE")
                {
                    currentState.reset();
                    currentStateName = "NONE";
                }
                else
                {
                    switchState(returned);
                }
            }
        }
    }
}
