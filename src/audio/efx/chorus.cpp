#include <featherkit/audio/efx/chorus.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    Chorus::Chorus() : 
        mWaveform(TRIANGLE),
        mPhase(90),
        mRate(1.1f),
        mDepth(0.1f),
        mFeedback(0.25f),
        mDelay(0.016f)
    {
        update();
    }

    void Chorus::setWaveform(Waveform waveform)
    {
        mWaveform = waveform;
        update();
    }

    Chorus::Waveform Chorus::getWaveform() const
    {
        return mWaveform;
    }

    void Chorus::setPhase(int32_t phase)
    {
        FEA_ASSERT(phase >= -180 && phase <= 180, "Chorus phase must be between -180 and 180!");
        mPhase = phase;
        update();
    }

    int32_t Chorus::getPhase() const
    {
        return mPhase;
    }

    void Chorus::setRate(float rate)
    {
        FEA_ASSERT(rate >= 0.0f && rate <= 10.0f, "Chorus rate must be between 0.0f and 10.0f!");
        mRate = rate;
        update();
    }

    float Chorus::getRate() const
    {
        return mRate;
    }

    void Chorus::setDepth(float depth)
    {
        FEA_ASSERT(depth >= 0.0f && depth <= 1.0f, "Chorus depth must be between 0.0f and 1.0f!");
        mDepth = depth;
        update();
    }

    float Chorus::getDepth() const
    {
        return mDepth;
    }

    void Chorus::setFeedback(float feedback)
    {
        FEA_ASSERT(feedback >= -1.0f && feedback <= 1.0f, "Chorus feedback must be between -1.0f and 1.0f!");
        mFeedback = feedback;
        update();
    }

    float Chorus::getFeedback() const
    {
        return mFeedback;
    }

    void Chorus::setDelay(float delay)
    {
        FEA_ASSERT(delay >= 0.0f && delay <= 0.016f, "Chorus delay must be between 0.0f and 0.16f!");
        mDelay = delay;
        update();
    }

    float Chorus::getDelay() const
    {
        return mDelay;
    }

    void Chorus::update()
    {
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_CHORUS);
        alEffecti(getEffectId(), AL_CHORUS_WAVEFORM, mWaveform);
        alEffecti(getEffectId(), AL_CHORUS_PHASE, mPhase);
        alEffectf(getEffectId(), AL_CHORUS_RATE, mRate);
        alEffectf(getEffectId(), AL_CHORUS_DEPTH, mDepth);
        alEffectf(getEffectId(), AL_CHORUS_FEEDBACK, mFeedback);
        alEffectf(getEffectId(), AL_CHORUS_DELAY, mDelay);
    }
}
