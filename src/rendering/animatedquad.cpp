#include <featherkit/rendering/animatedquad.h>

namespace fea
{
    AnimatedQuad::AnimatedQuad() : Quad(), clock(0), currentFrame(0), animate(false)
    {
    }

    AnimatedQuad::AnimatedQuad(float w, float h) : Quad(w, h), clock(0), currentFrame(0), animate(false)
    {
    }

    void AnimatedQuad::addAnimation(AnimationId id, std::weak_ptr<Animation> animation)
    {
        animations.emplace(id, animation);
    }

    void AnimatedQuad::setAnimation(AnimationId a, bool play)
    {
        if(a != currentAnimationId)
        {
            currentAnimation = animations.at(a);
            currentAnimationId = a;
            animate = play;
            currentFrame = 0;
        }
    }
    
    AnimationId AnimatedQuad::getAnimation() const
    {
        return currentAnimationId;
    }

    void AnimatedQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Quad::getRenderData(renderData, time);
        
        if(!currentAnimation.expired())
        {
            currentAnimation.lock()->getConstraints(renderData.constrainX, renderData.constrainY, currentFrame);
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
    
    void AnimatedQuad::stopAnimation()
    {
        animate = false;
    }

    void AnimatedQuad::setAnimationFrame(uint32_t frame)
    {
        currentFrame = frame;
    }
}
