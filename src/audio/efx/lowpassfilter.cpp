#include <featherkit/audio/efx/lowpassfilter.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    LowpassFilter::LowpassFilter() : 
        mGain(1.0f),
        mGainHF(1.0f)
    {
        update();
    }

    void LowpassFilter::setGain(float gain)
    {
        FEA_ASSERT(gain >= 0.0f && gain <= 1.0f, "LowpassFilter gain must be between 0.0f and 1.0f!");
        mGain = gain;
        update();
    }

    float LowpassFilter::getGain() const
    {
        return mGain;
    }

    void LowpassFilter::setGainHF(float gainHF)
    {
        FEA_ASSERT(gainHF >= 0.0f && gainHF <= 1.0f, "LowpassFilter gainHF must be between 0.0f and 1.0f!");
        mGainHF = gainHF;
        update();
    }

    float LowpassFilter::getGainHF() const
    {
        return mGainHF;
    }

    void LowpassFilter::update()
    {
        alFilteri(mEffectId, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
        alFilterf(mEffectId, AL_LOWPASS_GAIN, mGain);
        alFilterf(mEffectId, AL_LOWPASS_GAINHF, mGainHF);
    }
}
