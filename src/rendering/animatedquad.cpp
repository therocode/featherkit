#include <featherkit/rendering/animatedquad.h>
#include <iostream>

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
                currentFrame = rand() % currentAnimation->getFrameAmount();
            }
        }
    }
    
    const Animation& AnimatedQuad::getAnimation() const
    {
        return *currentAnimation;
    }

    void AnimatedQuad::getRenderData(RenderData& renderData, uint32_t time) const
    {
        Quad::getRenderData(renderData, time);

        std::cout << currentAnimation << " is what it points at \n";
        
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
                        }
                        else
                        {
                            currentFrame = 0;
                        }
                    }
                    break;

                case BACKWARDS:
                    
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
                        }
                        else
                        {
                            currentFrame = frameAmount - 1;
                        }
                    }
                    break;
                case BOUNCE:
                    break;
                case INV_BOUNCE:
                    break;
                case RANDOM:

                    if(clock == delay)
                    {
                        currentFrame = rand() % frameAmount;
                        clock = 0;
                    }
                    break;
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
