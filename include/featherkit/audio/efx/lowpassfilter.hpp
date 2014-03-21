#pragma once
#include <featherkit/audio/audiofilter.hpp>

namespace fea
{
    class LowPassFilter : public AudioFilter
    {
        public:
            LowPassFilter();
            void setGain(float gain);
            float getGain() const;
            void setGainHF(float gainHF);
            float getGainHF() const;
        private:
            void update();
            float mGain;
            float mGainHF;
    };
}
