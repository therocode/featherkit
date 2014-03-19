#pragma once
#include <featherkit/audio/audioeffect.hpp>

namespace fea
{
    class RingModulator : public AudioEffect
    {
        enum Waveform {SINE = 0, SAW = 1, SQUARE = 2};

        public:
            RingModulator();
            void setFrequency(float frequency);
            float getFrequency() const;
            void setHighPassCutoff(float highPassCutoff);
            float getHighPassCutoff() const;
            void setWaveform(Waveform waveform);
            Waveform getWaveform() const;
        private:
            void update();
            float mFrequency;
            float mHighPassCutoff;
            Waveform mWaveform;
    };
}
