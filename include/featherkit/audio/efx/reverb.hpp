#pragma once
#include <featherkit/audio/audioeffect.hpp>

namespace fea
{
    class Reverb : public AudioEffect
    {
        public:
            void setDecayTime(float decayTime);
            float getDecayTime() const;
        private:
            void update();
            float mDecayTime;
    };
}
