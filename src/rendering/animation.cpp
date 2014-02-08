#include <featherkit/rendering/animation.h>

namespace fea
{
    Animation::Animation() : mFrameAmount(0), mDelay(0), mLoop(true), mAnimBehaviour(FORWARDS)
    {
    }

    Animation::Animation(const glm::vec2& frameStart, const glm::vec2& frameSize, uint32_t fAmount, uint32_t d, bool l, AnimationBehaviour ab) : mStart(frameStart), mFrameSize(frameSize), mFrameAmount(fAmount), mDelay(d), mLoop(l), mAnimBehaviour(ab)
    {
    }

    void Animation::getConstraints(glm::vec4& constraints, uint32_t frame) const
    {
        constraints[0] = mStart.x + mFrameSize.x * (float)frame;
        constraints[1] = mStart.x + mFrameSize.x + mFrameSize.x * (float)frame;
        constraints[2] = mStart.y;
        constraints[3] = mStart.y + mFrameSize.y;
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

    AnimationBehaviour Animation::getAnimationBehaviour() const
    {
        return mAnimBehaviour;
    }
}
