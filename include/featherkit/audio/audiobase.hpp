#pragma once
#include <chrono>
#include <set>
#include <featherkit/audio/vec3f.hpp>
#include <featherkit/audio/audiofilter.hpp>

namespace fea
{
    class AudioFilter;

    class AudioBase
    {
        public:
            AudioBase();
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
            void setLooping(bool loop);
            bool isLooping() const;
            void setRelative(bool relative);
            bool isRelative();
            void setPlayOffset(std::chrono::milliseconds timePoint);
            std::chrono::milliseconds getPlayOffset() const;
            void addEffectSend(size_t slot);
            const std::set<size_t> getEffectSends() const;
            void setFilter(const AudioFilter& filter);
            const AudioFilter& getFilter() const;
            bool hasFilter() const;
            void clearFilter();
        protected:
            Vec3F mPosition;
            Vec3F mVelocity;
            float mPitch;
            float mGain;
            float mAttenuationFactor;
            float mAttenuationDistance;
            bool mLooping;
            bool mRelative;
            std::chrono::milliseconds mOffset;
            std::set<size_t> mEffectSends;
            const AudioFilter* mFilter;
    };
    /** @addtogroup Audio
     *@{
     *  @class AudioBase
     *@}
     ***
     *  @class AudioBase
     *  @brief Base class for playable audio
     *
     *  Classes inheriting this class will carry many properties of playable audio. These properties are:
     *      - Position - 3D Position in the audio scene.
     *      - Velocity - 3D Velocity. This can be used to create doppler effects.
     *      - Pitch - Modifier for the frequency.
     *      - Gain - Amplification of the sound, or in other words volume.
     *      - Attenuation Factor - Affects how far away the sound can be heard.
     *      - Looping - Toggle if the sound should be played repeatedly or not.
     *      - Relative - A relative audio is played with its position relative to the listener.
     *      - Play Offset - Decides where in the audio data the playback begins.
     *
     *  Check the setters of the properties to see what input they expect.
     ***
     *  @fn AudioBase::AudioBase()
     *  @brief Construct an AudioBase. 
     ***
     *  @fn void AudioBase::setPosition(const Vec3F& position)
     ***
     *  @fn const AudioBase::Vec3F& getPosition() const
     ***
     *  @fn void AudioBase::setVelocity(const Vec3F& velocity)
     ***
     *  @fn const AudioBase::Vec3F& getVelocity() const
     ***
     *  @fn void AudioBase::setPitch(float pitch)
     ***
     *  @fn float AudioBase::getPitch() const
     ***
     *  @fn void AudioBase::setGain(float pitch)
     ***
     *  @fn float AudioBase::getGain() const
     ***
     *  @fn void AudioBase::setAttenuationFactor(float attenuationFactor)
     ***
     *  @fn float AudioBase::getAttenuationFactor() const
     ***
     *  @fn void AudioBase::setAttenuationDistance(float attenuationDistance)
     ***
     *  @fn float AudioBase::getAttenuationDistance() const
     ***
     *  @fn void AudioBase::setLooping(bool loop)
     ***
     *  @fn bool AudioBase::isLooping() const
     ***
     *  @fn void AudioBase::setRelative(bool relative)
     ***
     *  @fn bool AudioBase::isRelative()
     ***
     *  @fn void AudioBase::setPlayOffset(std::chrono::milliseconds timePoint)
     ***
     *  @fn std::chrono::milliseconds AudioBase::getPlayOffset() const
     ***
     *  @fn void AudioBase::addEffectSend(size_t slot)
     ***
     *  @fn const AudioBase::std::set<size_t> getEffectSends() const
     ***
     *  @fn void AudioBase::setFilter(const AudioFilter& filter)
     ***
     *  @fn const AudioBase::AudioFilter& getFilter() const
     ***
     *  @fn bool AudioBase::hasFilter() const
     ***
     *  @fn void AudioBase::clearFilter()
     **/
}
