#include <framework/rendering/animation.h>

namespace windbreeze
{
    void Animation::getConstraints(glm::vec2& constraintX, glm::vec2& constraintY, uint32_t frame) const
    {
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
