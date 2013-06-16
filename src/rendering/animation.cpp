#include <framework/rendering/animation.h>

namespace windbreeze
{
    void Animation::getConstraints(glm::vec2& constraintX, glm::vec2& constraintY) const
    {
        constraintX[0] = start.x;
        constraintX[1] = start.x + frameSize.x;
        constraintY[0] = start.y;
        constraintY[1] = start.y + frameSize.y;

        (void)delay;
        (void)frameAmount;
        (void)loop;
    }
}
