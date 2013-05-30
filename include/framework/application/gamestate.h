#pragma once
#include <string>
#include <memory>

namespace windstorm
{
    class GameState
    {
        public:
            virtual void activate(std::string previousState) {}
            virtual void deactivate(std::string nextState) {}
            virtual void handOver(std::weak_ptr<GameState> previousState, std::string previousStateName) {}
            virtual void setup() {}
            virtual std::string run() = 0;
            virtual void destroy() {}
            virtual ~GameState() {}
    };
    /** @addtogroup Application
     *@{
     *  @class GameState
     *@}
     ***
     *  @class GameState
     *  @brief Abstract base class for specific states of a game application.
     *
     *  Derive this class to implement various game states. These would typically contain and set up all the data needed for that particular state.
     *  
     *  States are managed by a GameStateMachine instance and are not meant to be used directly. See GameStateMachine for more information.
     ***
     *  @fn virtual void GameState::activate(std::string previousState)
     *  @brief Activate a game state.
     *
     *  This function is called by the GameStateMachine before switching to this GameState. After this function is run, the state should be ready for per-frame execution.
     *  @param previousState Name of the preceding GameState. Used to adapt activation depending on which state it came from.
     ***
     *  @fn virtual void GameState::deactivate(std::string nextState)
     *  @brief Deactivate a game state.
     *
     *  This function is called by the GameStateMachine when it switches from this state to another state. Gives the GameState an opportunity to put itself in a deactivated state if needed.
     *  @param nextState Name of the next GameState of the GameStateMachine. Used to adapt deactivation depending on which state is the next one.
     ***
     *  @fn virtual void GameState::handOver(std::weak_ptr<GameState> previousState, std::string previousStateName)
     *  @brief Hand over data from another GameState instance to this one.
     *  
     *  This function is called by the GameStateMachine when it switches from this state to another state. When it is called, both this and the other GameState instance is in a deactivated state. The purpose of this function is to let this state fetch data from the previous GameState if needed. For example, if this GameState defines a high score state, it could fetch the final game score from the previous in-game state.
     *  @param previousState Pointer to the previous GameState.
     *  @param previousStateName Name of the previous GameState.
     ***/
}
