#include <fea/audio/efx/echo.hpp>
#include <fea/assert.hpp>

namespace fea
{
    Echo::Echo() : 
        mDelay(0.1f),
        mLRDelay(0.1f),
        mDamping(0.5f),
        mFeedback(0.5f),
        mSpread(-1.0f)
    {
        update();
    }


    void Echo::setDelay(float delay)
    {
        FEA_ASSERT(delay >= 0.0f && delay <= 0.207f, "Echo delay must be between 0.0f and 0.207f");
        mDelay = delay;
        update();
    }

    float Echo::getDelay() const
    {
        return mDelay;
    }

    void Echo::setLRDelay(float lrDelay)
    {
        FEA_ASSERT(lrDelay >= 0.0f && lrDelay <= 0.404f, "Echo lr delay must be between 0.0f and 0.404f!");
        mLRDelay = lrDelay;
        update();
    }

    float Echo::getLRDelay() const
    {
        return mLRDelay;
    }

    void Echo::setDamping(float damping)
    {
        FEA_ASSERT(damping >= 0.0f && damping <= 99.0f, "Echo damping must be between 0.0f and 99.0f!");
        mDamping = damping;
        update();
    }

    float Echo::getDamping() const
    {
        return mDamping;
    }

    void Echo::setFeedback(float feedback)
    {
        FEA_ASSERT(feedback >= 0.0f && feedback <= 1.0f, "Echo feedback must be between 0.0f and 1.0f!");
        mFeedback = feedback;
        update();
    }

    float Echo::getFeedback() const
    {
        return mFeedback;
    }

    void Echo::setSpread(float spread)
    {
        FEA_ASSERT(spread >= -1.0f && spread <= 1.0f, "Echo spread must be between -1.0f and 1.0f!");
        mSpread = spread;
        update();
    }

    float Echo::getSpread() const
    {
        return mSpread;
    }

    void Echo::update()
    {
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_ECHO);
        alEffectf(getEffectId(), AL_ECHO_DELAY, mDelay);
        alEffectf(getEffectId(), AL_ECHO_LRDELAY, mLRDelay);
        alEffectf(getEffectId(), AL_ECHO_DAMPING, mDamping);
        alEffectf(getEffectId(), AL_ECHO_FEEDBACK, mFeedback);
        alEffectf(getEffectId(), AL_ECHO_SPREAD, mSpread);
    }
}
