#pragma once
#include <al.h>

namespace fea
{
    class AudioEffect
    {
        public:
            AudioEffect();
            AudioEffect(const AudioEffect& other) = delete;
            AudioEffect(AudioEffect&& other);
            AudioEffect& operator=(const AudioEffect& other) = delete;
            AudioEffect& operator=(AudioEffect&& other);
            ~AudioEffect();
            void setGain(float gain);
            float getGain() const;
            void setAutoAdjustments(bool enabled);
            bool getAutoAdjustments() const;
        private:
            ALuint mEffectId;
            float mGain;
            bool mAutoSend;
    };
}
