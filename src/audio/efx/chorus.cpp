#include <featherkit/audio/efx/chorus.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    Chorus::Chorus() : 
        mWaveform(TRIANGLE),
        mPhase(90),
        mRate(1.1f)
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

    void Chorus::update()
    {
        std::cout << "chorus effect id " << mEffectId << "\n";
        std::cout << "al error: " << alGetError() << "\n";
        alEffecti(mEffectId, AL_EFFECT_TYPE, AL_EFFECT_CHORUS);
        std::cout << "al error2: " << (alGetError() == AL_INVALID_VALUE) << "\n";
        std::cout << "chorus is " << alGetEnumValue("AL_EFFECT_CHORUS") << "\n";
        std::cout << "version is " << alGetString(AL_VERSION) << "\n";
        //alEffecti(mEffectId, AL_CHORUS_WAVEFORM, mWaveform);
        //alEffecti(mEffectId, AL_CHORUS_PHASE, mPhase);
        //alEffecti(mEffectId, AL_CHORUS_RATE, mRate);

    }
}
