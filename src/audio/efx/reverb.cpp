#include <featherkit/audio/efx/reverb.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    Reverb::Reverb() :
        mDensity(1.0f),
        mDiffusion(1.0f),
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
        alEffectf(mEffectId, AL_REVERB_DECAY_TIME, mDecayTime);
    }
}
