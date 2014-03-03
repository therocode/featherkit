#pragma once
#include <featherkit/audio/audiosource.h>

namespace fea
{
    class AudioFile;

    class AudioSample : public AudioSource
    {
        public:
            void loadSampleData(const AudioFile& audioFile);
    };
}
