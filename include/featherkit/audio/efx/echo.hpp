#pragma once
#include <featherkit/audio/audioeffect.hpp>
#include <stdint.h>

namespace fea
{
    class Echo : public AudioEffect
    {
        public:
            Echo();
            void setDelay(float delay);
            float getDelay() const;
            void setLRDelay(float lrDelay);
            float getLRDelay() const;
            void setDamping(float damping);
            float getDamping() const;
            void setFeedback(float feedback);
            float getFeedback() const;
            void setSpread(float spread);
            float getSpread() const;
        private:
            void update();
            float mDelay;
            float mLRDelay;
            float mDamping;
            float mFeedback;
            float mSpread;
    };
    /** @addtogroup Audio
     *@{
     *  @class Echo
     *@}
     ***
     *  @class Echo
     *  @brief Echo Repeats the signal with decreasing intensity.
     *
     *  This effect is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the effect does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the effect.
     ***/
}
