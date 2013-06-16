#pragma once
#include <framework/glm/glm.hpp>
#include <stdint.h>

namespace windbreeze
{
    class Animation
    {
        public:
            Animation() {}
            Animation(glm::vec2 s, glm::vec2 fSize, uint32_t fAmount = 1, uint32_t d = 1, bool l = true) : start(s), frameSize(fSize), frameAmount(fAmount), delay(d), loop(l) {}
            void getConstraints(glm::vec2& constraintX, glm::vec2& constraintY) const;
        private:
            glm::vec2 start;
            glm::vec2 frameSize;
            uint32_t frameAmount = 1;
            uint32_t delay = 1;
            bool loop = true;
            //behaviour
    };
    //Animation
    //
    //Start x, y   in % of texture
    //FrameSize w, h  in % of texture
    //FrameAmount n  amount of frames in animation
    //Delay  t    time in frames between animation frames
    //Loop  should it loop or not
    //Behaviour  Forwards, Backwards, Bounce, ReverseBounce
}
