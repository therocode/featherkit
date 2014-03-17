#include <featherkit/audio/audioeffect.hpp>
#define AL_ALEXT_PROTOTYPES
#include <efx.h>
#include <utility>

namespace fea
{
    AudioEffect::AudioEffect()
    {
        alGenEffects(1, &mEffectId);
    }

    AudioEffect::AudioEffect(AudioEffect&& other) : 
        mEffectId(0)
    {
        std::swap(mEffectId, other.mEffectId);
    }

    AudioEffect& AudioEffect::operator=(AudioEffect&& other)
    {
        std::swap(mEffectId, other.mEffectId);

        return *this;
    }

    AudioEffect::~AudioEffect()
    {
        if(mEffectId != 0)
            alDeleteEffects(1, &mEffectId);
    }

    void AudioEffect::setGain(float gain)
    {
        mGain = gain;
    }

    float AudioEffect::getGain() const
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
