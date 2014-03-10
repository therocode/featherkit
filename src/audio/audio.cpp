#include <featherkit/audio/audio.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
        Audio::Audio() : mPosition({0.0f, 0.0f, 0.0f}),
                         mVelocity({0.0f, 0.0f, 0.0f}),
                         mPitch(1.0f),
                         mGain(1.0f),
                         mAttenuationFactor(1.0f),
                         mAttenuationDistance(1.0f),
                         mLoop(false),
                         mSample(nullptr),
                         mStream(nullptr)
        {
        }

        void Audio::setPosition(const Vec3F& position)
        {
            mPosition = position;
        }

        const Vec3F& Audio::getPosition() const
        {
            return mPosition;
        }

        void Audio::setVelocity(const Vec3F& velocity)
        {
            mVelocity = velocity;
        }

        const Vec3F& Audio::getVelocity() const
        {
            return mVelocity;
        }

        void Audio::setPitch(float pitch)
        {
            FEA_ASSERT(pitch > 0.0f, "Trying to set pitch to 0 or less! Given " + std::to_string(pitch));
            mPitch = pitch;
        }

        float Audio::getPitch() const
        {
            return mPitch;
        }

        void Audio::setGain(float gain)
        {
            FEA_ASSERT(gain > 0.0f, "Trying to set gain to 0 or less! Given " + std::to_string(gain));
            mGain = gain;
        }

        float Audio::getGain() const
        {
            return mGain;
        }

        void Audio::setAttenuationFactor(float attenuationFactor)
        {
            FEA_ASSERT(attenuationFactor > 0.0f, "Trying to set attenuation factor to 0 or less! Given " + std::to_string(attenuationFactor));
            mAttenuationFactor = attenuationFactor;
        }

        float Audio::getAttenuationFactor() const
        {
            return mAttenuationFactor;
        }

        void Audio::setAttenuationDistance(float attenuationDistance)
        {
            FEA_ASSERT(attenuationDistance > 0.0f, "Trying to set attenuation distance to 0 or less! Given " + std::to_string(attenuationDistance));
            mAttenuationDistance = attenuationDistance;
        }

        float Audio::getAttenuationDistance() const
        {
            return mAttenuationDistance;
        }

        void Audio::setLooping(bool looping)
        {
            mLoop = looping;
        }

        bool Audio::isLooping() const
        {
            return mLoop;
        }

        void Audio::setRelative(bool relative)
        {
            mRelative = relative;
        }

        bool Audio::isRelative()
        {
            return mRelative;
        }
            
        void Audio::setSource(AudioSample& sample)
        {
            mStream = nullptr;
            mSample = &sample;
        }

        void Audio::setSource(AudioStream& stream)
        {
            mSample = nullptr;
            mStream = &stream;
        }

        const AudioSample& Audio::getSample() const
        {
            FEA_ASSERT(mSample != nullptr, "Trying to access the sample from an audio instance which has no sample set!");
            return *mSample;
        }

        AudioStream& Audio::getStream()
        {
            FEA_ASSERT(mStream != nullptr, "Trying to access the stream from an audio instance which has no stream set!");
            return *mStream;
        }

        bool Audio::hasSample() const
        {
            return mSample != nullptr;
        }

        bool Audio::hasStream() const
        {
            return mStream != nullptr;
        }
}
