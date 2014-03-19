#pragma once
#include <featherkit/audio/audioeffect.hpp>
#include <stdint.h>

namespace fea
{
    class Distortion : public AudioEffect
    {
        public:
            Distortion();
            void setEdge(float edge);
            float getEdge() const;
            void setDistortionGain(float distortionGain);
            float getDistortionGain() const;
            void setLowPassCutoff(float lowPassCutoff);
            float getLowPassCutoff() const;
            void setEQCenter(float eqCenter);
            float getEQCenter() const;
            void setEQBandwidth(float eqBandwidth);
            float getEQBandwidth() const;
        private:
            void update();
            float mEdge;
            float mDistortionGain;
            float mLowPassCutoff;
            float mEQCenter;
            float mEQBandwidth;
    };
}
