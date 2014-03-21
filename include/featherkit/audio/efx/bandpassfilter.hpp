#pragma once
#include <featherkit/audio/audiofilter.hpp>

namespace fea
{
    class BandPassFilter : public AudioFilter
    {
        public:
            BandPassFilter();
            void setGain(float gain);
            float getGain() const;
            void setGainHF(float gainHF);
            float getGainHF() const;
            void setGainLF(float gainLF);
            float getGainLF() const;
        private:
            void update();
            float mGain;
            float mGainHF;
            float mGainLF;
    };
}
