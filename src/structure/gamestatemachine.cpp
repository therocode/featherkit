#include <featherkit/structure/gamestatemachine.h>
#include <sstream>

namespace fea
{
    GameStateException::GameStateException() : runtime_error("Game state not found")
    {
    }

    GameStateException::GameStateException(std::string msg) : runtime_error(msg.c_str())
    {
    }

    GameStateMachine::GameStateMachine() : mCurrentStateName("NONE")
    {
    }

    void GameStateMachine::addGameState(const std::string& name, std::shared_ptr<GameState> state)
    {
        state->setup();
        gameStates.insert(std::pair<std::string, std::shared_ptr<GameState> >(name, state));
    }

    void GameStateMachine::setCurrentState(const std::string& name)
    {
        if(gameStates.find(name) != gameStates.end())
        {
            if(mCurrentState.expired())
            {
                mCurrentState = gameStates.at(name);
                mCurrentState.lock()->activate("");
                mCurrentStateName = name;
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
        return mCurrentState.expired();
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
        if(nextStateName == mCurrentStateName)
        {
            return;
        }

        if(gameStates.find(nextStateName) != gameStates.end())
        {
            mCurrentState.lock()->deactivate(nextStateName);

            std::weak_ptr<GameState> previousState = mCurrentState;
            std::string previousStateName = mCurrentStateName;

            mCurrentState = gameStates.at(nextStateName);
            mCurrentStateName = nextStateName;

            mCurrentState.lock()->handOver(previousState, previousStateName);

            mCurrentState.lock()->activate(previousStateName);
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
        if(mCurrentStateName != "NONE")
        {
            std::string returned = mCurrentState.lock()->run();
            if(returned != "")
            {
                if(returned == "NONE")
                {
                    mCurrentState.reset();
                    mCurrentStateName = "NONE";
                }
                else
                {
                    switchState(returned);
                }
            }
        }
    }
}
