#pragma once
#include <featherkit/audio/audiofilter.hpp>

namespace fea
{
    class HighPassFilter : public AudioFilter
    {
        public:
            HighPassFilter();
            void setGain(float gain);
            float getGain() const;
            void setGainLF(float gainLF);
            float getGainLF() const;
        private:
            void update();
            float mGain;
            float mGainLF;
    };
}
