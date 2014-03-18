#include <featherkit/audio/efx/reverb.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    Reverb::Reverb() :
        mDensity(1.0f),
        mDiffusion(1.0f),
        mReverbGain(0.32f),
        mHFGain(0.89f),
        mDecayTime(1.49f)
    {
        update();
    }

    void Reverb::setDensity(float density)
    {
        FEA_ASSERT(density >= 0.0f && density <= 1.0f, "Reverb density must be between 0.0 and 1.0!");
        mDensity = density;
        update();
    }

    float Reverb::getDensity() const
    {
        return mDensity;
    }

    void Reverb::setDiffusion(float diffusion)
    {
        FEA_ASSERT(diffusion >= 0.0f && diffusion <= 1.0f, "Reverb diffusion must be between 0.0 and 1.0!");
        mDiffusion = diffusion;
        update();
    }

    float Reverb::getDiffusion() const
    {
        return mDiffusion;
    }

    void Reverb::setReverbGain(float reverbGain)
    {
        FEA_ASSERT(reverbGain >= 0.0f && reverbGain <= 1.0f, "Reverb gain must be between 0.0 and 1.0!");
        mReverbGain = reverbGain;
        update();
    }

    float Reverb::getReverbGain() const
    {
        return mReverbGain;
    }

    void Reverb::setHFGain(float hfGain)
    {
        FEA_ASSERT(hfGain >= 0.0f && hfGain <= 1.0f, "Reverb hf gain must be between 0.0 and 1.0!");
        mHFGain = hfGain;
        update();
    }

    float Reverb::getHFGain() const
    {
        return mHFGain;
    }

    void Reverb::setDecayTime(float decayTime)
    {
        FEA_ASSERT(decayTime >= 0.1f && decayTime <= 20.0f, "Reverb decay time must be between 0.1 and 20.0!");
        mDecayTime = decayTime;
        update();
    }

    float Reverb::getDecayTime() const
    {
        return mDecayTime;
    }

    void Reverb::update()
    {
        alEffecti(mEffectId, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
        alEffectf(mEffectId, AL_REVERB_DENSITY, mDensity);
        alEffectf(mEffectId, AL_REVERB_DIFFUSION, mDiffusion);
        alEffectf(mEffectId, AL_REVERB_GAIN, mReverbGain);
        alEffectf(mEffectId, AL_REVERB_GAINHF, mHFGain);
        alEffectf(mEffectId, AL_REVERB_DECAY_TIME, mDecayTime);
    }
}
