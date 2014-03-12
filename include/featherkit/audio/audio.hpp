#pragma once
#include <featherkit/audio/audiobase.hpp>

namespace fea
{
    class AudioSource;
    class AudioSample;

    class Audio : public AudioBase
    {
        public:
            Audio();
            void setSample(AudioSample& sample);
            const AudioSample& getSample() const;
            bool hasSample() const;
        private:
            AudioSample* mSample;
    };
}
