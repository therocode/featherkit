#pragma once
#include <featherkit/audio/vec3f.hpp>
#include <featherkit/audio/audiosample.hpp>
#include <featherkit/audio/audiostream.hpp>
#include <chrono>

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
            void setLooping(bool looping);
            bool isLooping() const;
            void setRelative(bool relative);
            bool isRelative();
            void setPlayOffset(std::chrono::milliseconds timePoint);
            std::chrono::milliseconds getPlayOffset() const;
            void setSource(AudioSample& sample);
            void setSource(AudioStream& stream);
            const AudioSample& getSample() const;
            AudioStream& getStream();
            bool hasSample() const;
            bool hasStream() const;
        private:
            Vec3F mPosition;
            Vec3F mVelocity;
            float mPitch;
            float mGain;
            float mAttenuationFactor;
            float mAttenuationDistance;
            bool mLoop;
            bool mRelative;
            std::chrono::milliseconds mOffset;
            AudioSample* mSample;
            AudioStream* mStream;
    };
}
