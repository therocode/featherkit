#pragma once
#include <featherkit/audio/audioeffect.hpp>
#include <stdint.h>

namespace fea
{
    class Chorus : public AudioEffect
    {
        enum Waveform {SINE = 0, TRIANGLE = 1};

        public:
            Chorus();
            void setWaveform(Waveform waveform);
            Waveform getWaveform() const;
            void setPhase(int32_t phase);
            int32_t getPhase() const;
            void setRate(float rate);
            float getRate() const;
        private:
            void update();
            Waveform mWaveform;
            int32_t mPhase;
            float mRate;
    };
}
