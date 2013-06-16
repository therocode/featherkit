#include <framework/rendering/animation.h>

namespace windbreeze
{
    void Animation::getConstraints(glm::vec2& constraintX, glm::vec2& constraintY) const
    {
        constraintX[0] = start.x + frameSize.x * currentFrame;
        constraintX[1] = start.x + frameSize.x + frameSize.x * currentFrame;
        constraintY[0] = start.y + frameSize.y * currentFrame;
        constraintY[1] = start.y + frameSize.y + frameSize.y * currentFrame;

        (void)delay;
        (void)frameAmount;
        (void)loop;
    }
    
    void Animation::tick()
    {
        clock++;

        currentFrame = (clock/delay) % frameAmount;
    }
}
