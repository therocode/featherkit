#pragma once
#include <featherkit/audio/vec3f.hpp>

namespace fea
{
    class AudioSource;

    class Audio
    {
        public:
            Audio();
            void setPosition(const Vec3F& position);
            const Vec3F& getPosition() const;
            void setVelocity(const Vec3F& velocity);
            const Vec3F& getVelocity() const;
            void setPitch(float pitch);
            float getPitch() const;
            void setGain(float pitch);
            float getGain() const;
            void setAttenuationFactor(float attenuationFactor);
            float getAttenuationFactor() const;
            void setAttenuationDistance(float attenuationDistance);
            float getAttenuationDistance() const;
            void setSource(AudioSource& source);
            const AudioSource& getSource() const;
            void setLooping(bool looping);
            bool getLooping() const;
        private:
            Vec3F mPosition;
            Vec3F mVelocity;
            float mPitch;
            float mGain;
            float mAttenuationFactor;
            float mAttenuationDistance;
            AudioSource* mSource;
            bool mLoop;
    };
}
