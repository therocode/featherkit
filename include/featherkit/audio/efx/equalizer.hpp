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
}
