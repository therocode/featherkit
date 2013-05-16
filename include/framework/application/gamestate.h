#pragma once
#include <string>

namespace windstorm
{
    class GameState
    {
        public:
            virtual void activate(std::string previousState) {}
            virtual void deactivate(std::string nextState) {}
            virtual void handOver(GameState* previousState) {}
            virtual void setup() {}
            virtual std::string run() = 0;
            virtual void destroy() {}
            virtual ~GameState() {}
    };
}
