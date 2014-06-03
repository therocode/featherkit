#pragma once
#include <fea/config.hpp>
#include <fea/audio/audioeffect.hpp>
#include <stdint.h>

namespace fea
{
    class FEA_API Chorus : public AudioEffect
    {
        public:
            enum Waveform {SINE = 0, TRIANGLE = 1};

        public:
            Chorus();
            void setWaveform(Waveform waveform);
            Waveform getWaveform() const;
            void setPhase(int32_t phase);
            int32_t getPhase() const;
            void setRate(float rate);
            float getRate() const;
            void setDepth(float depth);
            float getDepth() const;
            void setFeedback(float feedback);
            float getFeedback() const;
            void setDelay(float delay);
            float getDelay() const;
        private:
            void update();
            Waveform mWaveform;
            int32_t mPhase;
            float mRate;
            float mDepth;
            float mFeedback;
            float mDelay;
    };
    /** @addtogroup Audio
     *@{
     *  @class Chorus
     *@}
     ***
     *  @class Chorus
     *  @brief Chorus makes audio sound more "full" or "rich" through duplication.
     *
     *  This effect is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the effect does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the effect.
     ***/
}
