#pragma once
#include <featherkit/audio/audioeffect.hpp>

namespace fea
{
    class Reverb : public AudioEffect
    {
        public:
            Reverb();
            void setDensity(float density);
            float getDensity() const;
            void setDiffusion(float diffusion);
            float getDiffusion() const;
            void setDecayTime(float decayTime);
            float getDecayTime() const;
        private:
            void update();
            float mDensity;
            float mDiffusion;
            float mDecayTime;
    };
}
