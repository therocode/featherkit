#include <featherkit/audio/efx/reverb.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
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
        alEffectf(mEffectId, AL_REVERB_DECAY_TIME, mDecayTime);

        std::cout << "effect: " << mEffectId << " error: " << alGetError() << "\n";
    }
}
