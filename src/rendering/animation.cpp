#include <featherkit/rendering/animation.h>
#include <iostream>

namespace fea
{
    Animation::Animation() : frameAmount(0), delay(0), loop(true), animBehaviour(FORWARDS)
    {
    }

    Animation::Animation(float fStartX, float fStartY, float fWidth, float fHeight, uint32_t fAmount, uint32_t d, bool l, AnimationBehaviour ab) : start(glm::vec2(fStartX, fStartY)), frameSize(glm::vec2(fWidth, fHeight)), frameAmount(fAmount), delay(d), loop(l), animBehaviour(ab)
    {
    }

    Animation::Animation(glm::vec2 fStart, glm::vec2 fSize, uint32_t fAmount, uint32_t d, bool l, AnimationBehaviour ab) : start(fStart), frameSize(fSize), frameAmount(fAmount), delay(d), loop(l), animBehaviour(ab)
    {
    }

    void Animation::getConstraints(glm::vec2& constraintX, glm::vec2& constraintY, uint32_t frame) const
    {
        std::cout << "frame: " << frame << " startx " << start.x << " starty " << start.y << " framesize: " << frameSize.x << "x" << frameSize.y << "\n";
        constraintX[0] = start.x + frameSize.x * frame;
        constraintX[1] = start.x + frameSize.x + frameSize.x * frame;
        constraintY[0] = start.y;
        constraintY[1] = start.y + frameSize.y;
    }

    uint32_t Animation::getFrameAmount() const
    {
        return frameAmount;
    }

    uint32_t Animation::getDelay() const
    {
        return delay;
    }
            
    bool Animation::getLoop() const
    {
        return loop;
    }

    AnimationBehaviour Animation::getAnimationBehaviour() const
    {
        return animBehaviour;
    }
}
