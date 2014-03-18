#pragma once
#include <al.h>
#define AL_ALEXT_PROTOTYPES
#include <efx.h>

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
            ALuint getEffectId() const;
            void setGain(float gain);
            float getGain() const;
            void setAutoAdjustments(bool enabled);
            bool getAutoAdjustments() const;
        protected:
            ALuint mEffectId;
            float mGain;
            bool mAutoSend;
    };
}
