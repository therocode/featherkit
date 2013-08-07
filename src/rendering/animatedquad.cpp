#include <featherkit/rendering/animatedquad.h>

namespace fea
{
    AnimatedQuad::AnimatedQuad() : Quad(), currentAnimation(nullptr), clock(0), currentFrame(0), animate(false)
    {
    }

    AnimatedQuad::AnimatedQuad(float w, float h) : Quad(w, h), currentAnimation(nullptr), clock(0), currentFrame(0), animate(false)
    {
    }

    AnimatedQuad::AnimatedQuad(const glm::vec2& size) : Quad(size), currentAnimation(nullptr), clock(0), currentFrame(0), animate(false)
    {
    }

    void AnimatedQuad::setAnimation(const Animation& animation, bool play)
    {
        if(&animation != currentAnimation)
        {
            currentAnimation = &animation;
            animate = play;
            currentFrame = 0;
        }
    }
    
    const Animation& AnimatedQuad::getAnimation() const
    {
        return *currentAnimation;
    }

    void AnimatedQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Quad::getRenderData(renderData, time);
        
        if(currentAnimation != nullptr)
        {
            currentAnimation->getConstraints(renderData.constrainX, renderData.constrainY, currentFrame);
        }
    }
    
    void AnimatedQuad::tick()
    {
        if(animate && currentAnimation != nullptr)
        {
            clock++;
            
            uint32_t delay = currentAnimation->getDelay();
            uint32_t frameAmount = currentAnimation->getFrameAmount();
            bool loop = currentAnimation->getLoop();
            AnimationBehaviour animBehaviour = currentAnimation->getAnimationBehaviour();

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
        if(currentAnimation != nullptr)
        {
            animate = true;
            clock = startFrame * currentAnimation->getDelay();
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
