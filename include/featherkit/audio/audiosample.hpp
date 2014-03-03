#pragma once
#include <featherkit/audio/audiosource.hpp>

namespace fea
{
    class AudioFile;

    class AudioSample : public AudioSource
    {
        public:
            void loadSampleData(const AudioFile& audioFile);
    };
}
