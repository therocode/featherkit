#include <featherkit/audio/audiofilter.hpp>
#include <featherkit/assert.hpp>
#include <utility>

namespace fea
{
    AudioFilter::AudioFilter()
    {
#if !defined(__EMSCRIPTEN__)
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
#if !defined(__EMSCRIPTEN__)
        if(mFilterId != 0)
            alDeleteFilters(1, &mFilterId);
#endif
    }
    
    ALuint AudioFilter::getFilterId() const
    {
        return mFilterId;
    }
}
