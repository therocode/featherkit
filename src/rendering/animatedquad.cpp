#include <fea/rendering/animatedquad.hpp>
#include <fea/assert.hpp>

    namespace fea
    {
        AnimatedQuad::AnimatedQuad() : Quad(), mCurrentAnimation(nullptr), mClock(0), mCurrentFrame(0), mAnimate(false), mBack(false)
        {
        }

        AnimatedQuad::AnimatedQuad(const glm::vec2& size) : Quad(size), mCurrentAnimation(nullptr), mClock(0), mCurrentFrame(0), mAnimate(false), mBack(false)
        {
        }

        void AnimatedQuad::setAnimation(const Animation& animation, bool play)
        {
            mClock = 0;
            if(&animation != mCurrentAnimation)
            {
                mCurrentAnimation = &animation;
                mAnimate = play;

                AnimationBehavior animBehavior = mCurrentAnimation->getAnimationBehavior();

                if(animBehavior == FORWARDS || animBehavior == BOUNCE)
                {
                    mCurrentFrame = 0;
                }
                else if(animBehavior == BACKWARDS || animBehavior == INV_BOUNCE)
            {
                mCurrentFrame = mCurrentAnimation->getFrameAmount() - 1;
            }
            else if(animBehavior == RANDOM)
            {
                mCurrentFrame = (uint32_t)rand() % mCurrentAnimation->getFrameAmount();
            }
        }
        setConstraints();
    }
    
    const Animation& AnimatedQuad::getAnimation() const
    {
        FEA_ASSERT(mCurrentAnimation != nullptr, "No animation set!");
        return *mCurrentAnimation;
    }

    void AnimatedQuad::setTexture(const Texture& texture)
    {
        Quad::setTexture(texture);
        setConstraints();
    }

    void AnimatedQuad::tick()
    {
        if(mTexture)
        {
            if(mAnimate && mCurrentAnimation != nullptr)
            {
                mClock++;

                uint32_t delay = mCurrentAnimation->getDelay();
                uint32_t frameAmount = mCurrentAnimation->getFrameAmount();
                AnimationBehavior animBehavior = mCurrentAnimation->getAnimationBehavior();

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
                setConstraints();
            }
        }
    }
    
    void AnimatedQuad::playAnimation(uint32_t startFrame)
    {
        FEA_ASSERT(mCurrentAnimation != nullptr, "No animation set when calling playAnimation!");
        mAnimate = true;
        mClock = startFrame * mCurrentAnimation->getDelay();
        setConstraints();
    }
    
    void AnimatedQuad::stopAnimation()
    {
        mAnimate = false;
    }

    void AnimatedQuad::setAnimationFrame(uint32_t frame)
    {
        FEA_ASSERT(mCurrentAnimation != nullptr, "No animation set when calling setAnimationFrame!");
        mCurrentFrame = frame;
        setConstraints();
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
        bool loop = mCurrentAnimation->getLoop();
        uint32_t delay = mCurrentAnimation->getDelay();
        uint32_t frameAmount = mCurrentAnimation->getFrameAmount();

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
        bool loop = mCurrentAnimation->getLoop();
        uint32_t delay = mCurrentAnimation->getDelay();
        uint32_t frameAmount = mCurrentAnimation->getFrameAmount();

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
        bool loop = mCurrentAnimation->getLoop();
        uint32_t delay = mCurrentAnimation->getDelay();
        uint32_t frameAmount = mCurrentAnimation->getFrameAmount();

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
        bool loop = mCurrentAnimation->getLoop();
        uint32_t delay = mCurrentAnimation->getDelay();
        uint32_t frameAmount = mCurrentAnimation->getFrameAmount();

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

    void AnimatedQuad::setConstraints()
    {
        if(mTexture && mCurrentAnimation)
        {
            auto pixelConstraints = mCurrentAnimation->getConstraints(mCurrentFrame);
            auto textureSize = static_cast<glm::vec2>(mTexture->getSize());

            mConstraints = glm::vec4(glm::vec2(pixelConstraints.x, pixelConstraints.y) / textureSize.x, glm::vec2(pixelConstraints.z, pixelConstraints.w) / textureSize.y);

            mUniformsDirty = true;
        }
    }
}
