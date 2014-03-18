#include <featherkit/audio/audiobase.hpp>
#include <featherkit/assert.hpp>
#include <string>

namespace fea
{
    AudioBase::AudioBase() : 
            mPosition({0.0f, 0.0f, 0.0f}),
            mVelocity({0.0f, 0.0f, 0.0f}),
            mPitch(1.0f),
            mGain(1.0f),
            mAttenuationFactor(1.0f),
            mAttenuationDistance(1.0f),
        mLooping(false),
            mRelative(false),
        mOffset(0)
    {
    }

    void AudioBase::setPosition(const Vec3F& position)
    {
        mPosition = position;
    }

    const Vec3F& AudioBase::getPosition() const
    {
        return mPosition;
    }

    void AudioBase::setVelocity(const Vec3F& velocity)
    {
        mVelocity = velocity;
    }

    const Vec3F& AudioBase::getVelocity() const
    {
        return mVelocity;
    }

    void AudioBase::setPitch(float pitch)
    {
        FEA_ASSERT(pitch > 0.0f, "Trying to set pitch to 0 or less! Given " + std::to_string(pitch));
        mPitch = pitch;
    }

    float AudioBase::getPitch() const
    {
        return mPitch;
    }

    void AudioBase::setGain(float gain)
    {
        FEA_ASSERT(gain > 0.0f, "Trying to set gain to 0 or less! Given " + std::to_string(gain));
        mGain = gain;
    }

    float AudioBase::getGain() const
    {
        return mGain;
    }

    void AudioBase::setAttenuationFactor(float attenuationFactor)
    {
        FEA_ASSERT(attenuationFactor > 0.0f, "Trying to set attenuation factor to 0 or less! Given " + std::to_string(attenuationFactor));
        mAttenuationFactor = attenuationFactor;
    }

    float AudioBase::getAttenuationFactor() const
    {
        return mAttenuationFactor;
    }

    void AudioBase::setAttenuationDistance(float attenuationDistance)
    {
        FEA_ASSERT(attenuationDistance > 0.0f, "Trying to set attenuation distance to 0 or less! Given " + std::to_string(attenuationDistance));
        mAttenuationDistance = attenuationDistance;
    }

    float AudioBase::getAttenuationDistance() const
    {
        return mAttenuationDistance;
    }


    void AudioBase::setLooping(bool loop)
    {
        mLooping = loop;
    }

    bool AudioBase::isLooping() const
    {
        return mLooping;
    }

    void AudioBase::setRelative(bool relative)
    {
        mRelative = relative;
    }

    bool AudioBase::isRelative()
    {
        return mRelative;
    }

    void AudioBase::setPlayOffset(std::chrono::milliseconds timePoint)
    {
        mOffset = timePoint;
    }

    std::chrono::milliseconds AudioBase::getPlayOffset() const
    {
        return mOffset;
    }
    
    void AudioBase::addEffectSend(size_t slot)
    {
        mEffectSends.insert(slot);
    }
    
    const std::set<size_t> AudioBase::getEffectSends() const
    {
        return mEffectSends;
    }
}
