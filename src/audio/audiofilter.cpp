#include <featherkit/audio/audiofilter.hpp>
#include <featherkit/assert.hpp>
#define AL_ALEXT_PROTOTYPES
#include <efx.h>
#include <utility>

namespace fea
{
    AudioFilter::AudioFilter()
    {
        alGenFilters(1, &mFilterId);
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
        if(mFilterId != 0)
            alDeleteFilters(1, &mFilterId);
    }
    
    ALuint AudioFilter::getFilterId() const
    {
        return mFilterId;
    }
}
