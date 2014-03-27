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
            void setDecayHFRatio(float decayHFRatio);
            float getDecayHFRatio() const;
            void setReflectionsGain(float reflectionsGain);
            float getReflectionsGain() const;
            void setReflectionsDelay(float reflectionsDelay);
            float getReflectionsDelay() const;
            void setLateGain(float lateGain);
            float getLateGain() const;
            void setLateDelay(float lateDelay);
            float getLateDelay() const;
            void setRoomRolloffFactor(float roomRolloffFactor);
            float getRoomRolloffFactor() const;
            void setAirAbsorptionGainHF(float airAbsorptionGainHF);
            float getAirAbsorptionGainHF() const;
            void setDecayHFLimit(bool decayHFLimit);
            bool getDecayHFLimit() const;
        private:
            void update();
            float mDensity;
            float mDiffusion;
            float mReverbGain;
            float mHFGain;
            float mDecayTime;
            float mDecayHFRatio;
            float mReflectionsGain;
            float mReflectionsDelay;
            float mLateGain;
            float mLateDelay;
            float mRoomRolloffFactor;
            float mAirAbsorptionGainHF;
            bool mDecayHFLimit;
    };
    /** @addtogroup Audio
     *@{
     *  @class Reverb
     *@}
     ***
     *  @class Reverb
     *  @brief Reverb simulates acoustics of different environments.
     *
     *  This effect is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the effect does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the effect.
     ***/
}
