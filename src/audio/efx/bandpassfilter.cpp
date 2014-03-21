#include <featherkit/audio/efx/bandpassfilter.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    BandPassFilter::BandPassFilter() : 
        mGain(1.0f),
        mGainHF(1.0f),
        mGainLF(1.0f)
    {
        update();
    }

    void BandPassFilter::setGain(float gain)
    {
        FEA_ASSERT(gain >= 0.0f && gain <= 1.0f, "BandPassFilter gain must be between 0.0f and 1.0f!");
        mGain = gain;
        update();
    }

    float BandPassFilter::getGain() const
    {
        return mGain;
    }

    void BandPassFilter::setGainHF(float gainHF)
    {
        FEA_ASSERT(gainHF >= 0.0f && gainHF <= 1.0f, "BandPassFilter gainHF must be between 0.0f and 1.0f!");
        mGainHF = gainHF;
        update();
    }

    float BandPassFilter::getGainHF() const
    {
        return mGainHF;
    }

    void BandPassFilter::setGainLF(float gainLF)
    {
        FEA_ASSERT(gainLF >= 0.0f && gainLF <= 1.0f, "BandPassFilter gainLF must be between 0.0f and 1.0f!");
        mGainLF = gainLF;
        update();
    }

    float BandPassFilter::getGainLF() const
    {
        return mGainLF;
    }

    void BandPassFilter::update()
    {
        alFilteri(mFilterId, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
        alFilterf(mFilterId, AL_BANDPASS_GAIN, mGain);
        alFilterf(mFilterId, AL_BANDPASS_GAINHF, mGainHF);
        alFilterf(mFilterId, AL_BANDPASS_GAINLF, mGainLF);
    }
}
