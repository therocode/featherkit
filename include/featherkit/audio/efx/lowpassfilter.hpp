#pragma once
#include <featherkit/audio/audioeffect.hpp>

namespace fea
{
    class LowpassFilter : public AudioEffect
    {
        public:
            LowpassFilter();
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
