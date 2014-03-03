#pragma once
#include <string>
#include <map>
#include <featherkit/structure/gamestate.hpp>

namespace fea
{

    class GameStateMachine
    {
        public:
            GameStateMachine();
            void addGameState(const std::string& name, std::unique_ptr<GameState> state);
            void setCurrentState(const std::string& name);
            bool isFinished() const;
            void run();
        private:
            void switchState(const std::string& nextName);
            GameState* mCurrentState;
            std::string mCurrentStateName;
            std::map<std::string, std::unique_ptr<GameState>> gameStates;
    };
    
    /** @addtogroup Structure
     *@{
     *  @class GameStateMachine
     *@}
     ***
     *  @class GameStateMachine
     *  @brief Keeps track of several GameState instances and provides a way of conveniently switching between them.
     *
     *  Games are often divided into states. For example, even a very simple game might have the states "main menu", "high score", "in game" and "credits". This class manages states like this. A state is defined by the GameState class and has a unique name defined by a string. Every unique state should inherit this class. Instances of these classes are then added to the GameStateMachine using the GameStateMachine::addGameState function. When added, they are managed by the GameStateMachine and should not be handled manually at all. 
     *
     *  All added states will be unactive except one active state. When the function GameStateMachine::run is called, the GameState::run function of the currently active state will be called. 
     *
     *  The GameStateMachine class has functionality that lets you specify how the setup and destruction of the GameState instances work, and also how the transition between the states work. This is defined using virtual functions in the GameState classes. These functions are run at specific times. Here is a list of the functions and when they are called. For more information about them, see the documentation of GameState.
     *
     *  - GameState::setup - Called on a state when the state is added using GameStateMachine::addGameState.
     *  - GameState::activate - Called on a state when the GameStateMachine switches to it (last step in switching process).
     *  - GameState::deactivate - Called on a state when the GameStateMachine switches from it (first step in switching process).
     *  - GameState::handOver - Called on a state when switching from another state. Will receive the previous state as an argument (middle step in switching process).
     *  There are two ways for states to be switched. Either externally using a call to GameStateMachine::setCurrentState, or internally from the current active GameState if the GameState::run returns a non-null string (see GameState for more info). If the GameStateMachine switches to the state "NONE", it will be considered as not running and GameStateMachine::isFinished will return true. 
     *
     ***
     *  @fn void GameStateMachine::addGameState(const std::string& name, std::unique_ptr<GameState> state)
     *  @brief Add a GameState to the GameStateMachine.
     *
     *  After the GameState is added, it is completely managed by the GameStateMachine. Including freeing of the memory.
     *  Assert/undefined behavior if the name provided is already in use by another state.
     *  @param name Name of the GameState to add.
     *  @param state Pointer to the GameState instance to manage. Can take a GameState* and implicitly convert it.
     ***
     *  @fn void GameStateMachine::setCurrentState(const std::string& name)
     *  @brief Order the GameStateMachine to switch from the current GameState to the one having the name given.
     *
     *  Assert/undefined behavior if the given state does not exist.
     *  @param name Name of the state to switch to.
     ***
     *  @fn bool GameStateMachine::isFinished() const
     *  @brief Check if the GameStateMachine is in a terminated state.
     *  
     *  The GameStateMachine is defined to be in a terminated state if a switch to the state "NONE" has been made. In such a case this function will return true and GameStateMachine::run will have no effect.
     *  @return True if the GameStateMachine is in the "NONE" state, otherwise false.
     ***
     *  @fn void GameStateMachine::run()
     *  @brief Run a frame in the current active GameState. Will do nothing if GameStateMachine is terminated.
     ***/
}
