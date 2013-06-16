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
    }
    
    void AnimatedQuad::tick()
    {
        currentAnimation.tick();
    }
    
    void AnimatedQuad::playAnimation(uint32_t startFrame)
    {
        currentAnimation.play(startFrame);
    }
}
