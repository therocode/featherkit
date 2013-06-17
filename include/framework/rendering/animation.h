#pragma once
#include <framework/glm/glm.hpp>
#include <stdint.h>

namespace windbreeze
{
    enum AnimationBehaviour { FORWARDS, BACKWARDS };

    class Animation
    {
        public:
            Animation() {}
            Animation(glm::vec2 s, glm::vec2 fSize, uint32_t fAmount = 1, uint32_t d = 1, bool l = true, AnimationBehaviour ab = FORWARDS) : start(s), frameSize(fSize), frameAmount(fAmount), delay(d), loop(l) {setBehaviour(ab);}
            void getConstraints(glm::vec2& constraintX, glm::vec2& constraintY) const;
            void tick();
            void play(uint32_t startFrame = 0);
            void setBehaviour(AnimationBehaviour ab);
        private:
            glm::vec2 start;
            glm::vec2 frameSize;
            uint32_t frameAmount = 1;
            uint32_t delay = 1;
            bool loop = true;
            AnimationBehaviour animBehaviour = FORWARDS;

            bool animate = false;
            uint32_t clock = 0;
            uint32_t currentFrame = 0;
    };
}
