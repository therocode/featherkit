#include <framework/rendering/animatedquad.h>
#include <iostream>

namespace windbreeze
{
    void AnimatedQuad::setAnimation(Animation a)
    {
        currentAnimation = a;
    }
    
    void AnimatedQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Quad::getRenderData(renderData, time);
        
        currentAnimation.getConstraints(renderData.constrainX, renderData.constrainY);

        std::cout << "Constraints are now x: " << renderData.constrainX.x << " " << renderData.constrainX.y << " and y: " << renderData.constrainY.x << " " << renderData.constrainY.y << "\n";
    }
}
