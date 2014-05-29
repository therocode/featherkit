#include <fea/audio/audiofilter.hpp>
#include <fea/assert.hpp>
#include <utility>
#include "efx.h"

namespace fea
{
    AudioFilter::AudioFilter()
    {
#if !defined(NO_FEA_EFX)
        alGenFilters(1, &mFilterId);
#endif
    }

    AudioFilter::AudioFilter(AudioFilter&& other) : 
        mFilterId(0)
    {
        std::swap(mFilterId, other.mFilterId);
    }

    AudioFilter& AudioFilter::operator=(AudioFilter&& other)
    {
        std::swap(mFilterId, other.mFilterId);

        return *this;
    }

    AudioFilter::~AudioFilter()
    {
#if !defined(NO_FEA_EFX)
        if(mFilterId != 0)
            alDeleteFilters(1, &mFilterId);
#endif
    }
    
    ALuint AudioFilter::getFilterId() const
    {
        return mFilterId;
    }
}
