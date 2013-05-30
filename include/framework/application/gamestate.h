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
     *  @brief State of the art
     **/
}
