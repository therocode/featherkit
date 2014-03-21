#pragma once
#include <al.h>
#define AL_ALEXT_PROTOTYPES
#include <efx.h>

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
        protected:
            ALuint mFilterId;
    };
}
