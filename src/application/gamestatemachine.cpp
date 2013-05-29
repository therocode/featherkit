#include "framework/application/gamestatemachine.h"
#include <iostream>

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
                std::cout << "HEJ\n";
                currentState = gameStates.at(name);
                currentState.lock()->activate("");
                currentStateName = name;
            }
            else
            {
                std::cout << "HOJ\n";
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
            //error
        }
    }
    
    void GameStateMachine::run()
    {
        std::string returned = currentState.lock()->run();
        if(returned != "")
        {
            if(returned == "NONE")
            {
                currentState.reset();
            }
            else
            {
                switchState(returned);
            }
        }
    }
}
