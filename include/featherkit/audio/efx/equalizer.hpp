#pragma once
#include <featherkit/audio/audioeffect.hpp>

namespace fea
{
    class Equalizer : public AudioEffect
    {
        public:
            Equalizer();
            void setLowGain(float lowGain);
            float getLowGain() const;
            void setLowCutoff(float lowCutoff);
            float getLowCutoff() const;
            void setMid1Gain(float mid1Gain);
            float getMid1Gain() const;
            void setMid1Center(float mid1Center);
            float getMid1Center() const;
            void setMid1Width(float mid1Width);
            float getMid1Width() const;
            void setMid2Gain(float mid2Gain);
            float getMid2Gain() const;
            void setMid2Center(float mid2Center);
            float getMid2Center() const;
            void setMid2Width(float mid2Width);
            float getMid2Width() const;
            void setHighGain(float highGain);
            float getHighGain() const;
            void setHighCutoff(float highCutoff);
            float getHighCutoff() const;
        private:
            void update();
            float mLowGain;
            float mLowCutoff;
            float mMid1Gain;
            float mMid1Center;
            float mMid1Width;
            float mMid2Gain;
            float mMid2Center;
            float mMid2Width;
            float mHighGain;
            float mHighCutoff;
    };
    /** @addtogroup Audio
     *@{
     *  @class Equalizer
     *@}
     ***
     *  @class Equalizer
     *  @brief Equalizer Changes the frequency distribution of the signal.
     *
     *  This effect is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the effect does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the effect.
     ***/
}
