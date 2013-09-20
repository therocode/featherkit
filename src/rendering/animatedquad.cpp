#include <featherkit/rendering/animatedquad.h>

namespace fea
{
    AnimatedQuad::AnimatedQuad() : Quad(), currentAnimation(nullptr), clock(0), currentFrame(0), animate(false), back(false)
    {
    }

    AnimatedQuad::AnimatedQuad(float w, float h) : Quad(w, h), currentAnimation(nullptr), clock(0), currentFrame(0), animate(false), back(false)
    {
    }

    AnimatedQuad::AnimatedQuad(const glm::vec2& size) : Quad(size), currentAnimation(nullptr), clock(0), currentFrame(0), animate(false), back(false)
    {
    }

    void AnimatedQuad::setAnimation(const Animation& animation, bool play)
    {
        clock = 0;
        if(&animation != currentAnimation)
        {
            currentAnimation = &animation;
            animate = play;

            AnimationBehaviour animBehaviour = currentAnimation->getAnimationBehaviour();

            if(animBehaviour == FORWARDS || animBehaviour == BOUNCE)
            {
                currentFrame = 0;
            }
            else if(animBehaviour == BACKWARDS || animBehaviour == INV_BOUNCE)
            {
                currentFrame = currentAnimation->getFrameAmount() - 1;
            }
            else if(animBehaviour == RANDOM)
            {
                currentFrame = (uint32_t)rand() % currentAnimation->getFrameAmount();
            }
        }
    }
    
    const Animation& AnimatedQuad::getAnimation() const
    {
        return *currentAnimation;
    }

    void AnimatedQuad::tick()
    {
        if(animate && currentAnimation != nullptr)
        {
            clock++;
            
            uint32_t delay = currentAnimation->getDelay();
            uint32_t frameAmount = currentAnimation->getFrameAmount();
            AnimationBehaviour animBehaviour = currentAnimation->getAnimationBehaviour();

            if(frameAmount <= 1)
                return;

            switch(animBehaviour)
            {
                case FORWARDS:
                    animateForwards();
                    break;

                case BACKWARDS:
                    animateBackwards();
                    break;
                case BOUNCE:
                    animateBounce();
                    break;
                case INV_BOUNCE:
                    animateInvBounce();
                    break;
                case RANDOM:

                    if(clock == delay)
                    {
                        currentFrame = (uint32_t)rand() % frameAmount;
                        clock = 0;
                    }
                    break;
                default:
                    break;
            }

        }
        currentAnimation->getConstraints(constraints, currentFrame);
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
    
    uint32_t AnimatedQuad::getAnimationFrame() const
    {
        return currentFrame;
    }
    
    bool AnimatedQuad::isPlaying() const
    {
        return animate;
    }
    
    void AnimatedQuad::onAnimationEnd(std::function<void(void)> callback)
    {
        onEnd = callback;
    }

    void AnimatedQuad::animateForwards()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(clock == delay)
        {
            currentFrame++;
            clock = 0;
        }

        if(currentFrame == frameAmount)
        {
            if(!loop)
            {
                animate = false;
                currentFrame--;
                if(onEnd)
                    onEnd();
            }
            else
            {
                currentFrame = 0;
            }
        }
    }

    void AnimatedQuad::animateBackwards()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(clock == delay)
        {
            currentFrame--;
            clock = 0;
        }

        if(currentFrame == (uint32_t)-1)
        {
            if(!loop)
            {
                animate = false;
                currentFrame = 0;
                if(onEnd)
                    onEnd();
            }
            else
            {
                currentFrame = frameAmount - 1;
            }
        }
    }

    void AnimatedQuad::animateBounce()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(!back)
        {
            if(clock == delay)
            {
                currentFrame++;
                clock = 0;
            }

            if(currentFrame == frameAmount)
            {
                currentFrame -= 2;
                back = true;
            }
        }
        else
        {
            if(clock == delay)
            {
                currentFrame--;
                clock = 0;
            }

            if(currentFrame == (uint32_t)-1)
            {
                if(!loop)
                {
                    animate = false;
                    currentFrame = 0;
                    if(onEnd)
                        onEnd();
                }
                else
                {
                    currentFrame = 1;
                    back = false;
                }
            }
        }
    }

    void AnimatedQuad::animateInvBounce()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(!back)
        {
            if(clock == delay)
            {
                currentFrame--;
                clock = 0;
            }

            if(currentFrame == (uint32_t)-1)
            {
                currentFrame += 2;
                back = true;
            }
        }
        else
        {
            if(clock == delay)
            {
                currentFrame++;
                clock = 0;
            }

            if(currentFrame == frameAmount)
            {
                if(!loop)
                {
                    animate = false;
                    currentFrame--;
                    if(onEnd)
                        onEnd();
                }
                else
                {
                    currentFrame = frameAmount -2;
                    back = false;
                }
            }
        }
    }
}
