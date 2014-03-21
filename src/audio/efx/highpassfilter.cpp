#include <featherkit/audio/efx/highpassfilter.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    HighPassFilter::HighPassFilter() : 
        mGain(1.0f),
        mGainLF(1.0f)
    {
        update();
    }

    void HighPassFilter::setGain(float gain)
    {
        FEA_ASSERT(gain >= 0.0f && gain <= 1.0f, "HighPassFilter gain must be between 0.0f and 1.0f!");
        mGain = gain;
        update();
    }

    float HighPassFilter::getGain() const
    {
        return mGain;
    }

    void HighPassFilter::setGainLF(float gainLF)
    {
        FEA_ASSERT(gainLF >= 0.0f && gainLF <= 1.0f, "HighPassFilter gainLF must be between 0.0f and 1.0f!");
        mGainLF = gainLF;
        update();
    }

    float HighPassFilter::getGainLF() const
    {
        return mGainLF;
    }

    void HighPassFilter::update()
    {
        alFilteri(mFilterId, AL_FILTER_TYPE, AL_FILTER_HIGHPASS);
        alFilterf(mFilterId, AL_HIGHPASS_GAIN, mGain);
        alFilterf(mFilterId, AL_HIGHPASS_GAINLF, mGainLF);
    }
}
