#pragma once
#include <fea/config.hpp>
#include <chrono>
#include <set>
#include <fea/audio/vec3f.hpp>
#if !defined(FEA_NO_EFX)
#include <fea/audio/audiofilter.hpp>
#endif

namespace fea
{
    class AudioFilter;

    class FEA_API AudioBase
    {
        public:
            AudioBase();
            void setPosition(const Vec3F& position);
            const Vec3F& getPosition() const;
            void setVelocity(const Vec3F& velocity);
            const Vec3F& getVelocity() const;
            void setPitch(float pitch);
            float getPitch() const;
            void setGain(float gain);
            float getGain() const;
            void setAttenuationFactor(float attenuationFactor);
            float getAttenuationFactor() const;
            void setAttenuationDistance(float attenuationDistance);
            float getAttenuationDistance() const;
            void setLooping(bool loop);
            bool isLooping() const;
            void setRelative(bool relative);
            bool isRelative() const;
            void setPlayOffset(std::chrono::milliseconds timePoint);
            std::chrono::milliseconds getPlayOffset() const;
            void addEffectSend(size_t slot);
            const std::set<size_t> getEffectSends() const;
            void setFilter(const AudioFilter& filter);
            const AudioFilter& getFilter() const;
            bool hasFilter() const;
            void clearFilter();
        private:
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
     *      - Attenuation Distance - The distance at which the sound volume starts to dinimish.
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
     *  @brief Set the 3D position of the audio.
     *  @param position A 3D vector.
     ***
     *  @fn const Vec3F& AudioBase::getPosition() const
     *  @brief Get the 3D position.
     *  @return A vector with the position.
     ***
     *  @fn void AudioBase::setVelocity(const Vec3F& velocity)
     *  @brief Set the velocity of the audio.
     *
     *  The velocity is used to calculate doppler effects.
     *  @param velocity Vector with the new velocity.
     ***
     *  @fn const Vec3F& AudioBase::getVelocity() const
     *  @brief Get the velocity.
     *  @return A vector with the velocity.
     ***
     *  @fn void AudioBase::setPitch(float pitch)
     *  @brief Set the pitch modifier.
     *
     *  The pitch modifier acts as a multiplier for the pitch. A value of 1.0f means no change in pitch. From that, every halving or doubling goes down and up one octave in pitch respectively.
     *
     *  Assert/undefined behaviour when pitch is zero or less.
     *  @param pitch Modifier.
     ***
     *  @fn float AudioBase::getPitch() const
     *  @brief Get the pitch modifier.
     *  @return The pitch modifier.
     ***
     *  @fn void AudioBase::setGain(float gain)
     *  @brief Set the gain.
     *
     *  Gain is a multiplier for the amplitude or "loudness" of the sound. Can be used to make sounds more quiet. A value of 1.0f is standard. The total gain will be capped at 1.0f.
     *
     *  Assert/undefined behaviour when the given value is zero or less.
     *  @param gain The gain.
     ***
     *  @fn float AudioBase::getGain() const
     *  @brief Get the gain.
     *  @return The gain.
     ***
     *  @fn void AudioBase::setAttenuationFactor(float attenuationFactor)
     *  @brief Set the attenuation factor.
     *
     *  The attenuation factor is a multiplier which affects how fast the sound fades over distance. A higher number means that it becomes quiet faster. 1.0f is the default. By setting the value to zero, the sound is heard at an infinite distance.
     *  Assert/undefined behaviour if the value is less than zero.
     *  @param attenuationFactor Attenuation factor.
     ***
     *  @fn float AudioBase::getAttenuationFactor() const
     *  @brief Get the attenuation factor.
     *  @return The attenuation factor.
     ***
     *  @fn void AudioBase::setAttenuationDistance(float attenuationDistance)
     *  @brief Set the attenuation distance.
     *
     *  The attenuation distance is the distance at which the audio starts to become fainter. 1.0f is the detault. 
     *  Assert/undefined behaviour if the value is less than zero.
     *  @param attenuationDistance The distance.
     ***
     *  @fn float AudioBase::getAttenuationDistance() const
     *  @brief Get the attenuation distance.
     *  @return The attenuation distance.
     ***
     *  @fn void AudioBase::setLooping(bool loop)
     *  @brief Set the audio to loop or not.
     *  @param loop True if it should loop.
     ***
     *  @fn bool AudioBase::isLooping() const
     *  @brief Check if the audio is looping.
     *  @return True if it is looping.
     ***
     *  @fn void AudioBase::setRelative(bool relative)
     *  @brief Set the audio to be relative to the listener.
     *
     *  When the audio is relative to the listener, the position will be regarded as if the listener is at position 0,0,0 at all times.
     *  @param relative True if it should be relative.
     ***
     *  @fn bool AudioBase::isRelative() const
     *  @brief Check if the audio is heard relative to the listener.
     *  @return True if it is relative.
     ***
     *  @fn void AudioBase::setPlayOffset(std::chrono::milliseconds timePoint)
     *  @brief Set the time offset to start playback from.
     *
     *  If the audio supports it, the playback will be started from the given time point.
     *  @param timePoint Point in time from where the audio should be started.
     ***
     *  @fn std::chrono::milliseconds AudioBase::getPlayOffset() const
     *  @brief Get the time offset to start playback from.
     *  @return The amount of milliseconds.
     ***
     *  @fn void AudioBase::addEffectSend(size_t slot)
     *  @brief Adds an effect slot to send the played audio to.
     *
     *  This lets the audio send its rendered audio to an effect slot in the player playing it. More than one slot can be sent to. When sending to an effect slot, the effect and/or filter added to that slot will be taken into account.
     *  @param slot Slot to send to.
     ***
     *  @fn const std::set<size_t> AudioBase::getEffectSends() const
     *  @brief Get the effect slots being sent to.
     *  @return A set with all effects slots being sent to.
     ***
     *  @fn void AudioBase::setFilter(const AudioFilter& filter)
     *  @brief Set a filter to use.
     *  @param filter Filter to use.
     ***
     *  @fn const AudioFilter& AudioBase::getFilter() const
     *  @brief Get the filter currently in use.
     *
     *  Undefined behavior if no filter is set. Check if a filter is set by using AudioBase::hasFilter.
     *  @return Current filter.
     ***
     *  @fn bool AudioBase::hasFilter() const
     *  @brief Check if a filter is currently in use.
     *  @return True if a filter is in use.
     ***
     *  @fn void AudioBase::clearFilter()
     *  @brief Use no filter.
     *
     *  Use this to make the sound not use any filter.
     **/
}
