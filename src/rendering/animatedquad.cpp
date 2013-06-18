#include <framework/rendering/animatedquad.h>
#include <iostream>

namespace windbreeze
{
    void AnimatedQuad::addAnimation(AnimationId id, std::weak_ptr<Animation> animation)
    {
        animations.emplace(id, animation);
    }

    void AnimatedQuad::setAnimation(AnimationId a)
    {
        currentAnimation = animations.at(a);
    }
    
    void AnimatedQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Quad::getRenderData(renderData, time);
        
        if(!currentAnimation.expired())
        {
            currentAnimation.lock()->getConstraints(renderData.constrainX, renderData.constrainY, currentFrame);
        }
        else
        {
            std::cout << "AJJJJ AJJJ AJJJJJ JAJAJAJAJJAJJJJJJJ JAAAAAAAAAA SLUTA NU!\n";
        }
    }
    
    void AnimatedQuad::tick()
    {
        if(animate && !currentAnimation.expired())
        {
            clock++;
            
            std::shared_ptr<Animation> anim = currentAnimation.lock();
            uint32_t delay = anim->getDelay();
            uint32_t frameAmount = anim->getFrameAmount();
            bool loop = anim->getLoop();
            AnimationBehaviour animBehaviour = anim->getAnimationBehaviour();

            switch(animBehaviour)
            {
                case FORWARDS:
                    currentFrame = (clock/delay) % frameAmount;

                    if(!loop && currentFrame == frameAmount - 1)
                    {
                        animate = false;
                    }
                    break;

                case BACKWARDS:
                    currentFrame = (frameAmount - 1) - (clock/delay) % frameAmount;

                    if(!loop && currentFrame == 0)
                    {
                        animate = false;
                    }

                default:
                    break;
            }

        }
    }
    
    void AnimatedQuad::playAnimation(uint32_t startFrame)
    {
        if(!currentAnimation.expired())
        {
            animate = true;
            clock = startFrame * currentAnimation.lock()->getDelay();
        }
    }
}
