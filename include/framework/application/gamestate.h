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
     *  This function is called by the GameStateMachine when it switches from this state to another state. When it is called, both this and the other GameState instance will be in a deactivated state. The purpose of this function is to let this state fetch data from the previous GameState if needed. For example, if this GameState defines a high score state, it could fetch the final game score from the previous in-game state.
     *  @param previousState Pointer to the previous GameState.
     *  @param previousStateName Name of the previous GameState.
     ***
     *  @fn virtual void GameState::setup()
     *  @brief Setup a game state.
     *  
     *  This function is called by the GameStateMachine when the GameState is added to it. Hence this function should perform a one-time setup of the GameState if needed.
     ***
     *  @fn virtual std::string GameState::run() = 0
     *  @brief Perform per-frame logic of the state.
     *
     *  This function is called by the GameStateMachine every frame when this GameState is the current active state. This is where the logic of the state goes.
     *  @return Returns the name of the next GameState to switch to. If the string is not empty, the GameStateMachine will switch to that state if it exists. If "NONE" is returned, the GameStateMachine will deactivate the running state and be halted.
     ***
     *  @fn virtual void GameState::destroy()
     *  @brief Destroy a game state.
     *  
     *  This function is called by the GameStateMachine when it is destroyed. It will only ever be called once per GameState added to the GameStateMachine. This function is for freeing memory or clearing up other things that need it.
     ***
     *  @fn virtual GameState::~GameState()
     *  @brief Virtual destructor.
     * 
     *  This destructor is virtual to let the derived classes create their own destructors if they need to.
     ***/
}
