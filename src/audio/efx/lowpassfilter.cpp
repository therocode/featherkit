#include <fea/audio/efx/lowpassfilter.hpp>
#include <fea/assert.hpp>
#if !defined(FEA_NO_EFX)
#include "efx.h"
#endif

namespace fea
{
    LowPassFilter::LowPassFilter() : 
        mGain(1.0f),
        mGainHF(1.0f)
    {
        update();
    }

    void LowPassFilter::setGain(float gain)
    {
        FEA_ASSERT(gain >= 0.0f && gain <= 1.0f, "LowPassFilter gain must be between 0.0f and 1.0f!");
        mGain = gain;
        update();
    }

    float LowPassFilter::getGain() const
    {
        return mGain;
    }

    void LowPassFilter::setGainHF(float gainHF)
    {
        FEA_ASSERT(gainHF >= 0.0f && gainHF <= 1.0f, "LowPassFilter gainHF must be between 0.0f and 1.0f!");
        mGainHF = gainHF;
        update();
    }

    float LowPassFilter::getGainHF() const
    {
        return mGainHF;
    }

    void LowPassFilter::update()
    {
#if !defined(FEA_NO_EFX)
        alFilteri(getFilterId(), AL_FILTER_TYPE, AL_FILTER_LOWPASS);
        alFilterf(getFilterId(), AL_LOWPASS_GAIN, mGain);
        alFilterf(getFilterId(), AL_LOWPASS_GAINHF, mGainHF);
#endif
    }
}
