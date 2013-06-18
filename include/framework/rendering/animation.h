#pragma once
#include <framework/glm/glm.hpp>
#include <stdint.h>

namespace windbreeze
{
    enum AnimationBehaviour { FORWARDS, BACKWARDS };

    using AnimationId = size_t;

    class Animation
    {
        public:
            Animation() {}
            Animation(glm::vec2 s, glm::vec2 fSize, uint32_t fAmount = 1, uint32_t d = 1, bool l = true, AnimationBehaviour ab = FORWARDS) : start(s), frameSize(fSize), frameAmount(fAmount), delay(d), loop(l), animBehaviour(ab) {}
            void getConstraints(glm::vec2& constraintX, glm::vec2& constraintY, uint32_t frame) const;
            uint32_t getFrameAmount();
            uint32_t getDelay();
            bool getLoop();
            AnimationBehaviour getAnimationBehaviour();
        private:
            glm::vec2 start;
            glm::vec2 frameSize;
            uint32_t frameAmount = 1;
            uint32_t delay = 1;
            bool loop = true;
            AnimationBehaviour animBehaviour = FORWARDS;
    };
}
