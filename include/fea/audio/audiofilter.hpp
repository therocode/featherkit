#pragma once
#include "al.h"
#if !defined(__EMSCRIPTEN__)
#define AL_ALEXT_PROTOTYPES
#include "efx.h"
#endif

namespace fea
{
    class AudioFilter
    {
        public:
            AudioFilter();
            AudioFilter(const AudioFilter& other) = delete;
            AudioFilter(AudioFilter&& other);
            AudioFilter& operator=(const AudioFilter& other) = delete;
            AudioFilter& operator=(AudioFilter&& other);
            ~AudioFilter();
            ALuint getFilterId() const;
        private:
            ALuint mFilterId;
    };
    /** @addtogroup Audio
     *@{
     *  @class AudioFilter
     *@}
     ***
     *  @class AudioFilter
     *  @brief Base class for EFX based filters
     *
     *  Filters can be added to slots in the AudioPlayer class and directly on audio sources. A filter affects the frquencies of the audio in various frequency ranges.
     *
     *  All the filters are based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FFiltersExtensionGuide.pdf">EFX specification</a> and are hence not documented here. So have a look there to find out all about what the filters are, and what default values they have and which values they expect.
     ***
     *  @fn AudioFilter::AudioFilter()
     *  @brief Construct an AudioFilter. 
     ***
     *  @fn AudioFilter::AudioFilter(const AudioFilter& other) = delete
     *  @brief Deleted copy constructor.
     ***
     *  @fn AudioFilter::AudioFilter(AudioFilter&& other)
     *  @brief Move an AudioFilter.
     ***
     *  @fn AudioFilter& AudioFilter::operator=(const AudioFilter& other) = delete
     *  @brief Deleted assignment operator.
     ***
     *  @fn AudioFilter& AudioFilter::operator=(AudioFilter&& other)
     *  @brief Move an AudioFilter.
     ***
     *  @fn AudioFilter::~AudioFilter()
     *  @brief Destroy an AudioFilter.
     ***
     *  @fn ALuint AudioFilter::getFilterId() const
     *  @brief Get the internal OpenAL Id.
     *  @return The id.
     ***/
}
