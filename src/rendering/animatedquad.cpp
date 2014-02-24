#include <featherkit/rendering/animatedquad.h>
#include <featherkit/assert.h>

    namespace fea
    {
        AnimatedQuad::AnimatedQuad() : Quad(), currentAnimation(nullptr), mClock(0), mCurrentFrame(0), mAnimate(false), mBack(false)
        {
        }

        AnimatedQuad::AnimatedQuad(const glm::vec2& size) : Quad(size), currentAnimation(nullptr), mClock(0), mCurrentFrame(0), mAnimate(false), mBack(false)
        {
        }

        void AnimatedQuad::setAnimation(const Animation& animation, bool play)
        {
            mClock = 0;
            if(&animation != currentAnimation)
            {
                currentAnimation = &animation;
                mAnimate = play;

                AnimationBehavior animBehavior = currentAnimation->getAnimationBehavior();

                if(animBehavior == FORWARDS || animBehavior == BOUNCE)
                {
                    mCurrentFrame = 0;
                }
                else if(animBehavior == BACKWARDS || animBehavior == INV_BOUNCE)
            {
                mCurrentFrame = currentAnimation->getFrameAmount() - 1;
            }
            else if(animBehavior == RANDOM)
            {
                mCurrentFrame = (uint32_t)rand() % currentAnimation->getFrameAmount();
            }
        }
        currentAnimation->getConstraints(mConstraints, mCurrentFrame);
    }
    
    const Animation& AnimatedQuad::getAnimation() const
    {
        FEA_ASSERT(currentAnimation != nullptr, "No animation set!");
        return *currentAnimation;
    }

    void AnimatedQuad::tick()
    {
        if(mAnimate && currentAnimation != nullptr)
        {
            mClock++;
            
            uint32_t delay = currentAnimation->getDelay();
            uint32_t frameAmount = currentAnimation->getFrameAmount();
            AnimationBehavior animBehavior = currentAnimation->getAnimationBehavior();

            if(frameAmount <= 1)
                return;

            switch(animBehavior)
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

                    if(mClock == delay)
                    {
                        mCurrentFrame = (uint32_t)rand() % frameAmount;
                        mClock = 0;
                    }
                    break;
                default:
                    break;
            }
            currentAnimation->getConstraints(mConstraints, mCurrentFrame);
        }
    }
    
    void AnimatedQuad::playAnimation(uint32_t startFrame)
    {
        FEA_ASSERT(currentAnimation != nullptr, "No animation set when calling playAnimation!");
        mAnimate = true;
        mClock = startFrame * currentAnimation->getDelay();
        currentAnimation->getConstraints(mConstraints, mCurrentFrame);
    }
    
    void AnimatedQuad::stopAnimation()
    {
        mAnimate = false;
    }

    void AnimatedQuad::setAnimationFrame(uint32_t frame)
    {
        FEA_ASSERT(currentAnimation != nullptr, "No animation set when calling setAnimationFrame!");
        mCurrentFrame = frame;
        currentAnimation->getConstraints(mConstraints, mCurrentFrame);
    }
    
    uint32_t AnimatedQuad::getAnimationFrame() const
    {
        return mCurrentFrame;
    }
    
    bool AnimatedQuad::isPlaying() const
    {
        return mAnimate;
    }
    
    void AnimatedQuad::onAnimationEnd(std::function<void(void)> callback)
    {
        mOnEnd = callback;
    }

    void AnimatedQuad::animateForwards()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(mClock == delay)
        {
            mCurrentFrame++;
            mClock = 0;
        }

        if(mCurrentFrame == frameAmount)
        {
            if(!loop)
            {
                mAnimate = false;
                mCurrentFrame--;
                if(mOnEnd)
                    mOnEnd();
            }
            else
            {
                mCurrentFrame = 0;
            }
        }
    }

    void AnimatedQuad::animateBackwards()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(mClock == delay)
        {
            mCurrentFrame--;
            mClock = 0;
        }

        if(mCurrentFrame == (uint32_t)-1)
        {
            if(!loop)
            {
                mAnimate = false;
                mCurrentFrame = 0;
                if(mOnEnd)
                    mOnEnd();
            }
            else
            {
                mCurrentFrame = frameAmount - 1;
            }
        }
    }

    void AnimatedQuad::animateBounce()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(!mBack)
        {
            if(mClock == delay)
            {
                mCurrentFrame++;
                mClock = 0;
            }

            if(mCurrentFrame == frameAmount)
            {
                mCurrentFrame -= 2;
                mBack = true;
            }
        }
        else
        {
            if(mClock == delay)
            {
                mCurrentFrame--;
                mClock = 0;
            }

            if(mCurrentFrame == (uint32_t)-1)
            {
                if(!loop)
                {
                    mAnimate = false;
                    mCurrentFrame = 0;
                    if(mOnEnd)
                        mOnEnd();
                }
                else
                {
                    mCurrentFrame = 1;
                    mBack = false;
                }
            }
        }
    }

    void AnimatedQuad::animateInvBounce()
    {
        bool loop = currentAnimation->getLoop();
        uint32_t delay = currentAnimation->getDelay();
        uint32_t frameAmount = currentAnimation->getFrameAmount();

        if(!mBack)
        {
            if(mClock == delay)
            {
                mCurrentFrame--;
                mClock = 0;
            }

            if(mCurrentFrame == (uint32_t)-1)
            {
                mCurrentFrame += 2;
                mBack = true;
            }
        }
        else
        {
            if(mClock == delay)
            {
                mCurrentFrame++;
                mClock = 0;
            }

            if(mCurrentFrame == frameAmount)
            {
                if(!loop)
                {
                    mAnimate = false;
                    mCurrentFrame--;
                    if(mOnEnd)
                        mOnEnd();
                }
                else
                {
                    mCurrentFrame = frameAmount -2;
                    mBack = false;
                }
            }
        }
    }
}
