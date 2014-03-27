#include <featherkit/audio/efx/reverb.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    Reverb::Reverb() :
        mDensity(1.0f),
        mDiffusion(1.0f),
        mReverbGain(0.32f),
        mHFGain(0.89f),
        mDecayTime(1.49f),
        mDecayHFRatio(0.83f),
        mReflectionsGain(0.05f),
        mReflectionsDelay(0.007f),
        mLateGain(1.26f),
        mLateDelay(0.011f),
        mRoomRolloffFactor(0.0f),
        mAirAbsorptionGainHF(0.994f),
        mDecayHFLimit(true)
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

    void Reverb::setDecayHFRatio(float decayHFRatio)
    {
        FEA_ASSERT(decayHFRatio >= 0.1f && decayHFRatio <= 2.0f, "Reverb decay HF ratio must be between 0.1 and 2.0!");
        mDecayHFRatio = decayHFRatio;
        update();
    }

    float Reverb::getDecayHFRatio() const
    {
        return mDecayHFRatio;
    }

    void Reverb::setReflectionsGain(float reflectionsGain)
    {
        FEA_ASSERT(reflectionsGain >= 0.0f && reflectionsGain <= 3.16f, "Reverb reflections gain must be between 0.0 and 3.16!");
        mReflectionsGain = reflectionsGain;
        update();
    }

    float Reverb::getReflectionsGain() const
    {
        return mReflectionsGain;
    }

    void Reverb::setReflectionsDelay(float reflectionsDelay)
    {
        FEA_ASSERT(reflectionsDelay >= 0.0f && reflectionsDelay <= 0.3f, "Reverb reflections delay must be between 0.0 and 0.3!");
        mReflectionsDelay = reflectionsDelay;
        update();
    }

    float Reverb::getReflectionsDelay() const
    {
        return mReflectionsDelay;
    }

    void Reverb::setLateGain(float lateGain)
    {
        FEA_ASSERT(lateGain >= 0.0f && lateGain <= 10.0f, "Reverb late gain must be between 0.0 and 10.0!");
        mLateGain = lateGain;
        update();
    }

    float Reverb::getLateGain() const
    {
        return mLateGain;
    }

    void Reverb::setLateDelay(float lateDelay)
    {
        FEA_ASSERT(lateDelay >= 0.0f && lateDelay <= 0.1f, "Reverb late delay must be between 0.0 and 0.1!");
        mLateDelay = lateDelay;
        update();
    }

    float Reverb::getLateDelay() const
    {
        return mLateDelay;
    }

    void Reverb::setRoomRolloffFactor(float roomRolloffFactor)
    {
        FEA_ASSERT(roomRolloffFactor >= 0.0f && roomRolloffFactor <= 10.0f, "Reverb room rolloff factor must be between 0.0 and 10.0!");
        mRoomRolloffFactor = roomRolloffFactor;
        update();
    }

    float Reverb::getRoomRolloffFactor() const
    {
        return mRoomRolloffFactor;
    }

    void Reverb::setAirAbsorptionGainHF(float airAbsorptionGainHF)
    {
        FEA_ASSERT(airAbsorptionGainHF >= 0.892f && airAbsorptionGainHF <= 1.0f, "Reverb air absorption gain HF must be between 0.892 and 1.0!");
        mAirAbsorptionGainHF = airAbsorptionGainHF;
        update();
    }

    float Reverb::getAirAbsorptionGainHF() const
    {
        return mAirAbsorptionGainHF;
    }

    void Reverb::setDecayHFLimit(bool decayHFLimit)
    {
        mDecayHFLimit = decayHFLimit;
        update();
    }

    bool Reverb::getDecayHFLimit() const
    {
        return mDecayHFLimit;
    }

    void Reverb::update()
    {
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_REVERB);
        alEffectf(getEffectId(), AL_REVERB_DENSITY, mDensity);
        alEffectf(getEffectId(), AL_REVERB_DIFFUSION, mDiffusion);
        alEffectf(getEffectId(), AL_REVERB_GAIN, mReverbGain);
        alEffectf(getEffectId(), AL_REVERB_GAINHF, mHFGain);
        alEffectf(getEffectId(), AL_REVERB_DECAY_TIME, mDecayTime);
        alEffectf(getEffectId(), AL_REVERB_DECAY_HFRATIO, mDecayHFRatio);
        alEffectf(getEffectId(), AL_REVERB_REFLECTIONS_GAIN, mReflectionsGain);
        alEffectf(getEffectId(), AL_REVERB_REFLECTIONS_DELAY, mReflectionsDelay);
        alEffectf(getEffectId(), AL_REVERB_LATE_REVERB_GAIN, mLateGain);
        alEffectf(getEffectId(), AL_REVERB_LATE_REVERB_DELAY, mLateDelay);
        alEffectf(getEffectId(), AL_REVERB_ROOM_ROLLOFF_FACTOR, mRoomRolloffFactor);
        alEffectf(getEffectId(), AL_REVERB_AIR_ABSORPTION_GAINHF, mAirAbsorptionGainHF);
        alEffecti(getEffectId(), AL_REVERB_DECAY_HFLIMIT, mDecayHFLimit ? AL_TRUE : AL_FALSE);
    }
}
