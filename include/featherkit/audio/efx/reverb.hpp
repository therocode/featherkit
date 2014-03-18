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
            void setReverbGain(float reverbGain);
            float getReverbGain() const;
            void setHFGain(float hfGain);
            float getHFGain() const;
            void setDecayTime(float decayTime);
            float getDecayTime() const;
        private:
            void update();
            float mDensity;
            float mDiffusion;
            float mReverbGain;
            float mHFGain;
            float mDecayTime;
    };
}
