#include <fea/audio/efx/flanger.hpp>
#include <fea/assert.hpp>

namespace fea
{
    Flanger::Flanger() : 
        mWaveform(TRIANGLE),
        mPhase(0),
        mRate(0.27f),
        mDepth(1.0f),
        mFeedback(-0.5f),
        mDelay(0.002f)
    {
        update();
    }

    void Flanger::setWaveform(Waveform waveform)
    {
        mWaveform = waveform;
        update();
    }

    Flanger::Waveform Flanger::getWaveform() const
    {
        return mWaveform;
    }

    void Flanger::setPhase(int32_t phase)
    {
        FEA_ASSERT(phase >= -180 && phase <= 180, "Flanger phase must be between -180 and 180!");
        mPhase = phase;
        update();
    }

    int32_t Flanger::getPhase() const
    {
        return mPhase;
    }

    void Flanger::setRate(float rate)
    {
        FEA_ASSERT(rate >= 0.0f && rate <= 10.0f, "Flanger rate must be between 0.0f and 10.0f!");
        mRate = rate;
        update();
    }

    float Flanger::getRate() const
    {
        return mRate;
    }

    void Flanger::setDepth(float depth)
    {
        FEA_ASSERT(depth >= 0.0f && depth <= 1.0f, "Flanger depth must be between 0.0f and 1.0f!");
        mDepth = depth;
        update();
    }

    float Flanger::getDepth() const
    {
        return mDepth;
    }

    void Flanger::setFeedback(float feedback)
    {
        FEA_ASSERT(feedback >= -1.0f && feedback <= 1.0f, "Flanger feedback must be between -1.0f and 1.0f!");
        mFeedback = feedback;
        update();
    }

    float Flanger::getFeedback() const
    {
        return mFeedback;
    }

    void Flanger::setDelay(float delay)
    {
        FEA_ASSERT(delay >= 0.0f && delay <= 0.004f, "Flanger delay must be between 0.0f and 0.004f!");
        mDelay = delay;
        update();
    }

    float Flanger::getDelay() const
    {
        return mDelay;
    }

    void Flanger::update()
    {
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_FLANGER);
        alEffecti(getEffectId(), AL_FLANGER_WAVEFORM, mWaveform);
        alEffecti(getEffectId(), AL_FLANGER_PHASE, mPhase);
        alEffectf(getEffectId(), AL_FLANGER_RATE, mRate);
        alEffectf(getEffectId(), AL_FLANGER_DEPTH, mDepth);
        alEffectf(getEffectId(), AL_FLANGER_FEEDBACK, mFeedback);
        alEffectf(getEffectId(), AL_FLANGER_DELAY, mDelay);
    }
}
