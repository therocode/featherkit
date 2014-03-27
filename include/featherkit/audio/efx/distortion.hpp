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
    /** @addtogroup Audio
     *@{
     *  @class Distortion
     *@}
     ***
     *  @class Distortion
     *  @brief Distortion makes the sound noisy/fuzzy by over amplifying the sound wave.
     *
     *  This effect is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the effect does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the effect.
     ***/
}
