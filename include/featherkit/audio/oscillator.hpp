#pragma once
#include <featherkit/audio/audiostream.hpp>

namespace fea
{
    class Oscillator : public AudioStream
    {
        public:
            Oscillator();
            virtual AudioData fetchBufferData(size_t bufferIndex) override;
            void setFrequency(float frequency);
        private:
            float mFrequency;
            double mTheta;
    };
}
