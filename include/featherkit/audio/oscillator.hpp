#pragma once
#include <featherkit/audio/audiostream.hpp>

namespace fea
{
    class Oscillator : public AudioStream
    {
        public:
            Oscillator();
            virtual void fillBufferData(size_t sampleIndex, AudioData& toFill) override;
            void setFrequency(float frequency);
        private:
            float mFrequency;
            double mTheta;
    };
}
