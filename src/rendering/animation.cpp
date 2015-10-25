#include <fea/rendering/animation.hpp>

namespace fea
{
    Animation::Animation() : mFrameAmount(0), mDelay(0), mLoop(true), mAnimBehavior(FORWARDS)
    {
    }

    Animation::Animation(const glm::ivec2& frameStart, const glm::ivec2& frameSize, uint32_t fAmount, uint32_t d, bool l, AnimationBehavior ab) : mStart(frameStart), mFrameSize(frameSize), mFrameAmount(fAmount), mDelay(d), mLoop(l), mAnimBehavior(ab)
    {
    }

    glm::ivec4 Animation::getConstraints(uint32_t frame) const
    {
        glm::ivec4 constraints;
        constraints[0] = mStart.x + mFrameSize.x * frame;
        constraints[1] = mStart.x + mFrameSize.x + mFrameSize.x * frame;
        constraints[2] = mStart.y;
        constraints[3] = mStart.y + mFrameSize.y;
        return constraints;
    }

    uint32_t Animation::getFrameAmount() const
    {
        return mFrameAmount;
    }

    uint32_t Animation::getDelay() const
    {
        return mDelay;
    }
            
    bool Animation::getLoop() const
    {
        return mLoop;
    }

    AnimationBehavior Animation::getAnimationBehavior() const
    {
        return mAnimBehavior;
    }
}
