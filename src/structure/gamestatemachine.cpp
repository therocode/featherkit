#include <featherkit/structure/gamestatemachine.h>
#include <featherkit/assert.h>
#include <sstream>

namespace fea
{
    GameStateMachine::GameStateMachine() : mCurrentStateName("NONE"), mCurrentState(nullptr)
    {
    }

    void GameStateMachine::addGameState(const std::string& name, std::unique_ptr<GameState> state)
    {
        FEA_ASSERT(gameStates.find(name) == gameStates.end(), "Trying to add state called " + name + " but such a state name already exists!");
        state->setup();
        gameStates.emplace(name, std::move(state));
    }

    void GameStateMachine::setCurrentState(const std::string& name)
    {
        FEA_ASSERT(gameStates.find(name) != gameStates.end(), "Trying to set to state called " + name + " but such a state does not exist!");

        if(mCurrentState == nullptr)
        {
            mCurrentState = gameStates.at(name).get();
            mCurrentState->activate("");
            mCurrentStateName = name;
        }
        else
        {
            switchState(name);
        }
    }
    
    bool GameStateMachine::isFinished() const
    {
        return mCurrentState == nullptr;
    }

    void GameStateMachine::switchState(const std::string& nextStateName)
    {
        if(nextStateName == mCurrentStateName)
        {
            return;
        }

        mCurrentState->deactivate(nextStateName);

        GameState* previousState = mCurrentState;
        std::string previousStateName = mCurrentStateName;

        mCurrentState = gameStates.at(nextStateName).get();
        mCurrentStateName = nextStateName;

        mCurrentState->handOver(*previousState, previousStateName);

        mCurrentState->activate(previousStateName);
    }
    
    void GameStateMachine::run()
    {
        if(mCurrentStateName != "NONE")
        {
            std::string returned = mCurrentState->run();
            if(returned != "")
            {
                if(returned == "NONE")
                {
                    mCurrentState = nullptr;
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
