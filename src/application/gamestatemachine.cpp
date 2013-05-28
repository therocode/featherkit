#include "framework/application/gamestatemachine.h"

namespace windstorm
{
    void GameStateMachine::addGameState(const std::string& name, GameState* state)
    {
        state->setup();
        gameStates.insert(std::pair<std::string, GameState*>(name, state));
    }

    void GameStateMachine::setCurrentState(const std::string& name)
    {
        if(gameStates.find(name) != gameStates.end())
        {
            if(currentState == nullptr)
            {
                currentState = gameStates.at(name);
                currentState->activate("");
                currentStateName = name;
            }
            else
            {
                switchState(name);
            }
        }
        else
        {
            //error
        }
    }
    
    bool GameStateMachine::isFinished()
    {
        return currentState == nullptr;
    }

    GameStateMachine::~GameStateMachine()
    {
        for(auto statePair : gameStates)
        {
            statePair.second->destroy();
            delete statePair.second;
        }
    }

    void GameStateMachine::switchState(const std::string& nextStateName)
    {
        if(gameStates.find(nextStateName) != gameStates.end())
        {
            currentState->deactivate(nextStateName);

            GameState* previousState = currentState;
            std::string previousStateName = currentStateName;

            currentState = gameStates.at(nextStateName);
            currentStateName = nextStateName;

            currentState->handOver(previousState, previousStateName);

            currentState->activate(previousStateName);
        }
        else
        {
            //error
        }
    }
    
    void GameStateMachine::run()
    {
        std::string returned = currentState->run();
        if(returned != "")
        {
            if(returned == "NONE")
            {
                currentState = nullptr;
            }
            else
            {
                switchState(returned);
            }
        }
    }
}
