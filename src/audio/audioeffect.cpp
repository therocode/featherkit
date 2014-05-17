#include <fea/audio/audioeffect.hpp>
#include <fea/assert.hpp>
#include <utility>

namespace fea
{
    AudioEffect::AudioEffect() : 
        mGain(1.0f),
        mAutoSend(true)
    {
#if !defined(__EMSCRIPTEN__)
        alGenEffects(1, &mEffectId);
#endif
    }

    AudioEffect::AudioEffect(AudioEffect&& other) : 
        mEffectId(0),
        mGain(1.0f),
        mAutoSend(true)
    {
        std::swap(mEffectId, other.mEffectId);
        std::swap(mGain, other.mGain);
        std::swap(mAutoSend, other.mAutoSend);
    }

    AudioEffect& AudioEffect::operator=(AudioEffect&& other)
    {
        std::swap(mEffectId, other.mEffectId);
        std::swap(mGain, other.mGain);
        std::swap(mAutoSend, other.mAutoSend);

        return *this;
    }

    AudioEffect::~AudioEffect()
    {
#if !defined(__EMSCRIPTEN__)
        if(mEffectId != 0)
            alDeleteEffects(1, &mEffectId);
#endif
    }
    
    ALuint AudioEffect::getEffectId() const
    {
        return mEffectId;
    }

    void AudioEffect::setEffectGain(float gain)
    {
        FEA_ASSERT(gain >= 0.0f && gain <= 1.0f, "Effect gain must be in the range of 0.0f and 1.0f");
        mGain = gain;
    }

    float AudioEffect::getEffectGain() const
    {
        return mGain;
    }

    void AudioEffect::setAutoAdjustments(bool enabled)
    {
        mAutoSend = enabled;
    }
     
    bool AudioEffect::getAutoAdjustments() const
    {
        return mAutoSend;
    }
}
