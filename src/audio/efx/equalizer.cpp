#include <fea/audio/efx/equalizer.hpp>
#include <fea/assert.hpp>
#include "efx.h"

namespace fea
{
    Equalizer::Equalizer() : 
        mLowGain(1.0f),
        mLowCutoff(200.0f),
        mMid1Gain(1.0f),
        mMid1Center(500.0f),
        mMid1Width(1.0f),
        mMid2Gain(1.0f),
        mMid2Center(3000.0f),
        mMid2Width(1.0f),
        mHighGain(1.0f),
        mHighCutoff(6000.0f)
    {
        update();
    }

    void Equalizer::setLowGain(float lowGain)
    {
        FEA_ASSERT(lowGain >= 0.126f && lowGain <= 7.943f, "Equalizer lowGain must be between 0.126f and 7.943f!");
        mLowGain = lowGain;
        update();
    }

    float Equalizer::getLowGain() const
    {
        return mLowGain;
    }

    void Equalizer::setLowCutoff(float lowCutoff)
    {
        FEA_ASSERT(lowCutoff >= 50.0f && lowCutoff <= 800.0f, "Equalizer lowCutoff must be between 50.0f and 800.0f!");
        mLowCutoff = lowCutoff;
        update();
    }

    float Equalizer::getLowCutoff() const
    {
        return mLowCutoff;
    }

    void Equalizer::setMid1Gain(float mid1Gain)
    {
        FEA_ASSERT(mid1Gain >= 0.126f && mid1Gain <= 7.943f, "Equalizer mid1Gain must be between 0.126f and 7.943f!");
        mMid1Gain = mid1Gain;
        update();
    }

    float Equalizer::getMid1Gain() const
    {
        return mMid1Gain;
    }

    void Equalizer::setMid1Center(float mid1Center)
    {
        FEA_ASSERT(mid1Center >= 200.0f && mid1Center <= 3000.0f, "Equalizer mid1Center must be between 200.0f and 3000.0f!");
        mMid1Center = mid1Center;
        update();
    }

    float Equalizer::getMid1Center() const
    {
        return mMid1Center;
    }

    void Equalizer::setMid1Width(float mid1Width)
    {
        FEA_ASSERT(mid1Width >= 0.01f && mid1Width <= 1.0f, "Equalizer mid1Width must be between 0.01f and 1.0f!");
        mMid1Width = mid1Width;
        update();
    }

    float Equalizer::getMid1Width() const
    {
        return mMid1Width;
    }

    void Equalizer::setMid2Gain(float mid2Gain)
    {
        FEA_ASSERT(mid2Gain >= 0.126f && mid2Gain <= 7.943f, "Equalizer mid2Gain must be between 0.126f and 7.943f!");
        mMid2Gain = mid2Gain;
        update();
    }

    float Equalizer::getMid2Gain() const
    {
        return mMid2Gain;
    }

    void Equalizer::setMid2Center(float mid2Center)
    {
        FEA_ASSERT(mid2Center >= 1000.0f && mid2Center <= 8000.0f, "Equalizer mid2Center must be between 1000.0f and 8000.0f!");
        mMid2Center = mid2Center;
        update();
    }

    float Equalizer::getMid2Center() const
    {
        return mMid2Center;
    }

    void Equalizer::setMid2Width(float mid2Width)
    {
        FEA_ASSERT(mid2Width >= 0.01f && mid2Width <= 1.0f, "Equalizer mid2Width must be between 0.01f and 1.0f!");
        mMid2Width = mid2Width;
        update();
    }

    float Equalizer::getMid2Width() const
    {
        return mMid2Width;
    }

    void Equalizer::setHighGain(float highGain)
    {
        FEA_ASSERT(highGain >= 0.126f && highGain <= 7.943f, "Equalizer highGain must be between 0.126f and 7.943f!");
        mHighGain = highGain;
        update();
    }

    float Equalizer::getHighGain() const
    {
        return mHighGain;
    }

    void Equalizer::setHighCutoff(float highCutoff)
    {
        FEA_ASSERT(highCutoff >= 4000.0f && highCutoff <= 16000.0f, "Equalizer highCutoff must be between 4000.0f and 16000.0f!");
        mHighCutoff = highCutoff;
        update();
    }

    float Equalizer::getHighCutoff() const
    {
        return mHighCutoff;
    }

    void Equalizer::update()
    {
        std::cout << "error1: " << alGetError() << "\n";
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
        alEffectf(getEffectId(), AL_EQUALIZER_LOW_GAIN, mLowGain);
        alEffectf(getEffectId(), AL_EQUALIZER_LOW_CUTOFF, mLowCutoff);
        alEffectf(getEffectId(), AL_EQUALIZER_MID1_GAIN, mMid1Gain);
        alEffectf(getEffectId(), AL_EQUALIZER_MID1_CENTER, mMid1Center);
        alEffectf(getEffectId(), AL_EQUALIZER_MID1_WIDTH, mMid1Width);
        alEffectf(getEffectId(), AL_EQUALIZER_MID2_GAIN, mMid2Gain);
        alEffectf(getEffectId(), AL_EQUALIZER_MID2_CENTER, mMid2Center);
        alEffectf(getEffectId(), AL_EQUALIZER_MID2_WIDTH, mMid2Width);
        alEffectf(getEffectId(), AL_EQUALIZER_HIGH_GAIN, mHighGain);
        alEffectf(getEffectId(), AL_EQUALIZER_HIGH_CUTOFF, mHighCutoff);
    }
}
