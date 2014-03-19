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
}
