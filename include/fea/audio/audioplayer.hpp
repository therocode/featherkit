#pragma once
#include <fea/audio/openal.hpp>
#include <stack>
#include <unordered_map>
#include <fea/audio/playsource.hpp>
#include <fea/audio/listener.hpp>
#include <fea/audio/effectslot.hpp>
#include <fea/audio/audioeffect.hpp>
#include <fea/audio/audiofilter.hpp>
#include <thread>
#include <mutex>
#include <vector>

namespace fea
{
    using AudioHandle = size_t;
    class Audio;
    class AudioStream;

    enum PlayStatus {PLAYING, PAUSED, EXPIRED};

    class AudioPlayer
    {
        public:
            AudioPlayer();
            AudioPlayer(const AudioPlayer& other) = delete;
            AudioPlayer(AudioPlayer&& other) = delete;
            AudioPlayer& operator=(const AudioPlayer& other) = delete;
            AudioPlayer& operator=(AudioPlayer&& other) = delete;
            ~AudioPlayer();
            AudioHandle play(Audio& audio);
            AudioHandle play(AudioStream& stream);
            void pause(AudioHandle handle);
            void resume(AudioHandle handle);
            void stop(AudioHandle handle);
            size_t getMaxSoundsPlaying() const;
            size_t getNumSoundsPlaying() const;
            PlayStatus getStatus(AudioHandle handle) const;
            void setPosition(AudioHandle handle, const Vec3F& position) const;
            Vec3F getPosition(AudioHandle handle);
            void setVelocity(AudioHandle handle, const Vec3F& velocity) const;
            Vec3F getVelocity(AudioHandle handle);
            void setPitch(AudioHandle handle, float pitch) const;
            float getPitch(AudioHandle handle);
            void setGain(AudioHandle handle, float gain) const;
            float getGain(AudioHandle handle);
            void setAttenuationFactor(AudioHandle handle, float attenuationFactor);
            float getAttenuationFactor(AudioHandle handle) const;
            void setAttenuationDistance(AudioHandle handle, float attenuationDistance);
            float getAttenuationDistance(AudioHandle handle) const;
            void setLooping(AudioHandle handle, bool looping);
            bool isLooping(AudioHandle handle) const;
            void setRelative(AudioHandle handle, bool relative);
            bool isRelative(AudioHandle handle) const;
            void setListener(const Listener& listener);
            const Listener& getListener() const;
            size_t getMaxAuxiliarySend() const;
            void setSlotEffect(const AudioEffect& effect, size_t slot);
            void clearSlotEffect(size_t slot);
            void setSlotFilter(const AudioFilter& filter, size_t slot);
            void clearSlotFilter(size_t slot);
            void update();
        private:
            void setupSources(size_t maxSoundAmount);
            void renewFinishedSources();
            ALCdevice*  mAudioDevice;
            ALCcontext* mAudioContext;
            ALCint mMaxAuxSend;
            std::stack<PlaySource> mIdleSources;
            const size_t mMaxSoundsPlaying;
            size_t mNumSoundsPlaying;
            Listener mListener;

            //recycle sources
            AudioHandle mNextHandle;
            std::unordered_map<AudioHandle, PlaySource> mPlayingSources;
            mutable std::mutex mSourcesMutex;

#if !defined(__EMSCRIPTEN__)
            //streaming threads
            class Stream
            {
                public:
                    Stream(const PlaySource& source, AudioStream& audioStream);
                    Stream(Stream&& other);
                    void streamerThread();
                    void start();
                    void stop();
                private:
                    const PlaySource& mSource;
                    AudioStream& mStream;
                    bool mIsFinishing;
                    std::thread mStreamerThread;
            };
#else
            class Stream
            {
                public:
                    Stream(const PlaySource& source, AudioStream& audioStream);
                    Stream(Stream&& other);
                    void update();
                private:
                    const PlaySource& mSource;
                    AudioStream& mStream;
            };
#endif
            std::unordered_map<ALuint, Stream> mStreams;

            //effect stuff
            std::vector<EffectSlot> mEffectSlots;
    };
    /** @addtogroup Audio
     *@{
     *  @enum PlayStatus
     *  @class AudioPlayer
     *@}
     ***
     *  @enum PlayStatus
     *  @brief Status of an audio being played.
     ***
     *  @class AudioPlayer
     *  @brief Plays audio sources.
     *
     *  Using the audio player, sampled audio and audio streams can be played. Upon playing, a handle to the playing audio will be given and this can be used to change properties of the audio in real time if desired. 
     *
     *  There is a limit on how many sounds can be played at once which can be accessed with getMaxSoundsPlaying. When more sounds than this is played, nothing will happen. The getNumSoundsPlaying function can be used to check how many sounds are currently being played.
     *
     *  The AudioPlayer always has a Listener. The listener can be thought of as the "ear" in the audio scene. The position and orientation of the listener will affect how the sounds are positioned in the speakers when being played.
     *  
     *  Furthermore, effects and filters such as reverb, echo, distiortion and a handful of other ones can be added to the player's effect slots to enable richer audio environments.
     ***
     *  @fn AudioPlayer::AudioPlayer()
     *  @brief Construct an AudioPlayer. 
     ***
     *  @fn AudioPlayer::AudioPlayer(const AudioPlayer& other) = delete
     *  @brief Deleted copy constructor.
     ***
     *  @fn AudioPlayer::AudioPlayer(AudioPlayer&& other)
     *  @brief Move an AudioPlayer.
     ***
     *  @fn AudioPlayer& AudioPlayer::operator=(const AudioPlayer& other) = delete
     *  @brief Deleted assignment operator.
     ***
     *  @fn AudioPlayer& AudioPlayer::operator=(AudioPlayer&& other)
     *  @brief Move an AudioPlayer.
     ***
     *  @fn AudioPlayer::~AudioPlayer()
     *  @brief Destroy an AudioPlayer.
     ***
     *  @fn AudioHandle AudioPlayer::play(Audio& audio)
     *  @brief Play a sampled audio.
     *
     *  The returned handle can be used to manipulate the properties of the audio in real time. Changing the properties of the Audio instance after playback has been started will not affect the playing audio.
     *
     *  When the sound has finished playing, the handle will be invalid and if used nothing will happen.
     *  @param audio Audio to play.
     *  @return Handle to the playing audio.
     ***
     *  @fn AudioHandle AudioPlayer::play(AudioStream& stream)
     *  @brief Play an AudioStream.
     *
     *  The returned handle can be used to manipulate the properties of the audio stream in real time. Changing the properties of the AudioStream instance after playback has been started will not affect the playing audio.
     *
     *  When the sound has finished playing, the handle will be invalid and if used nothing will happen.
     *  @param stream AudioStream to play.
     *  @return Handle to the playing audio stream.
     ***
     *  @fn void AudioPlayer::pause(AudioHandle handle)
     *  @brief Pause a playing audio.
     *
     *  Resume using the resume function.
     *  @param handle Handle to the audio to pause.
     ***
     *  @fn void AudioPlayer::resume(AudioHandle handle)
     *  @brief Resume a paused audio.
     *  @param handle Handle to the audio to resume.
     ***
     *  @fn void AudioPlayer::stop(AudioHandle handle)
     *  @brief Stop an audio.
     *
     *  Stopping an audio terminates its playing completely and the handle will be invalidated. Hence playback cannot be resumed but the audio has to be played again using the play function.
     *  @param handle Handle to the audio to stop.
     ***
     *  @fn size_t AudioPlayer::getMaxSoundsPlaying() const
     *  @brief Check how many simultaneous audio playbacks the player can handle.
     *  @return Amount.
     ***
     *  @fn size_t AudioPlayer::getNumSoundsPlaying() const
     *  @brief Check how many sounds are being played right now.
     *  @return Amount.
     ***
     *  @fn void AudioPlayer::setPosition(AudioHandle handle, const Vec3F& position)
     *  @brief Set the 3D position of the audio of a sound that is being played.
     *  @param handle Handle to the audio being played.
     *  @param position A 3D vector.
     ***
     *  @fn PlayStatus AudioPlayer::getStatus(AudioHandle handle) const
     *  @brief Get the current status of a sound.
     *  @return Current status.
     ***
     *  @fn const Vec3F& AudioPlayer::getPosition(AudioHandle handle) const
     *  @brief Get the 3D position of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return A vector with the position.
     ***
     *  @fn void AudioPlayer::setVelocity(AudioHandle handle, const Vec3F& velocity)
     *  @brief Set the velocity of the audio of a sound that is being played.
     *
     *  The velocity is used to calculate doppler effects.
     *  @param handle Handle to the audio being player.
     *  @param velocity Vector with the new velocity of a sound that is being played.
     ***
     *  @fn const Vec3F& AudioPlayer::getVelocity(AudioHandle handle) const
     *  @brief Get the velocity of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return A vector with the velocity.
     ***
     *  @fn void AudioPlayer::setPitch(AudioHandle handle, float pitch)
     *  @brief Set the pitch modifier of a sound that is being played.
     *
     *  The pitch modifier acts as a multiplier for the pitch. A value of 1.0f means no change in pitch. From that, every halving or doubling goes down and up one octave in pitch respectively.
     *
     *  Assert/undefined behaviour when pitch is zero or less.
     *  @param handle Handle to the audio being player.
     *  @param pitch Modifier of a sound that is being played.
     ***
     *  @fn float AudioPlayer::getPitch(AudioHandle handle) const
     *  @brief Get the pitch modifier of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return The pitch modifier.
     ***
     *  @fn void AudioPlayer::setGain(AudioHandle handle, float gain)
     *  @brief Set the gain of a sound that is being played.
     *
     *  Gain is a multiplier for the amplitude or "loudness" of the sound. Can be used to make sounds more quiet. A value of 1.0f is standard. The total gain will be capped at 1.0f.
     *
     *  Assert/undefined behaviour when the given value is zero or less.
     *  @param handle Handle to the audio being player.
     *  @param gain The gain.
     ***
     *  @fn float AudioPlayer::getGain(AudioHandle handle) const
     *  @brief Get the gain of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return The gain.
     ***
     *  @fn void AudioPlayer::setAttenuationFactor(AudioHandle handle, float attenuationFactor)
     *  @brief Set the attenuation factor of a sound that is being played.
     *
     *  The attenuation factor is a multiplier which affects how fast the sound fades over distance. A higher number means that it becomes quiet faster. 1.0f is the default. By setting the value to zero, the sound is heard at an infinite distance.
     *  Assert/undefined behaviour if the value is less than zero.
     *  @param handle Handle to the audio being player.
     *  @param attenuationFactor Attenuation factor.
     ***
     *  @fn float AudioPlayer::getAttenuationFactor(AudioHandle handle) const
     *  @brief Get the attenuation factor of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return The attenuation factor.
     ***
     *  @fn void AudioPlayer::setAttenuationDistance(AudioHandle handle, float attenuationDistance)
     *  @brief Set the attenuation distance of a sound that is being played.
     *
     *  The attenuation distance is the distance at which the audio starts to become fainter. 1.0f is the detault. 
     *  Assert/undefined behaviour if the value is less than zero.
     *  @param handle Handle to the audio being player.
     *  @param attenuationDistance The distance.
     ***
     *  @fn float AudioPlayer::getAttenuationDistance(AudioHandle handle) const
     *  @brief Get the attenuation distance of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return The attenuation distance.
     ***
     *  @fn void AudioPlayer::setLooping(AudioHandle handle, bool loop)
     *  @brief Set the audio to loop or not of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @param loop True if it should loop.
     ***
     *  @fn bool AudioPlayer::isLooping(AudioHandle handle) const
     *  @brief Check if the audio is looping of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return True if it is looping.
     ***
     *  @fn void AudioPlayer::setRelative(AudioHandle handle, bool relative)
     *  @brief Set the audio to be relative to the listener of a sound that is being played.
     *
     *  When the audio is relative to the listener, the position will be regarded as if the listener is at position 0,0,0 at all times.
     *  @param handle Handle to the audio being player.
     *  @param relative True if it should be relative.
     ***
     *  @fn bool AudioPlayer::isRelative(AudioHandle handle)
     *  @brief Check if the audio is heard relative to the listener of a sound that is being played.
     *  @param handle Handle to the audio being player.
     *  @return True if it is relative.
     ***
     *  @fn void AudioPlayer::setListener(const Listener& listener)
     *  @brief Set the listener to use.
     *  @param listener Listener.
     ***
     *  @fn const Listener& AudioPlayer::getListener() const
     *  @brief Get the current listener.
     *
     *  This can be used to modify the listener.
     *  @return Current listener.
     ***
     *  @fn size_t AudioPlayer::getMaxAuxiliarySend() const
     *  @brief Get the amount of effect slots that one source can send to.
     *  @return Amount.
     ***
     *  @fn void AudioPlayer::setSlotEffect(const AudioEffect& effect, size_t slot)
     *  @brief Set which effect a slot should use.
     *
     *  There are four slots available to set the effect for. When an effect is set to a particular slot, sources can send to it to have the effect applied on them. If changes are made to the effect, it has to be re-applied using this function for the changes to take effect.
     *  Assert/undefined behavior when the slot parameter is higher than three.
     *  @param effect Effect to set to the slot.
     *  @param slot Index of the slot to use.
     ***
     *  @fn void AudioPlayer::clearSlotEffect(size_t slot)
     *  @brief Clears the effect attached to a slot.
     *
     *  Assert/undefined behavior when the slot parameter is higher than three.
     *  @param slot Index of the slot to clear.
     ***
     *  @fn void AudioPlayer::setSlotFilter(const AudioFilter& filter, size_t slot)
     *  @brief Set a filter to use for an effect slot.
     *
     *  If a filter is applied on an effect slot, the audio that results from the effect will be filtered. If changes are made to the filter, it has to be re-applied using this function for the changes to take effect.
     *  Assert/undefined behavior when the slot parameter is higher than three.
     *  @param filter Filter to set to the slot.
     *  @param slot Index of the slot to use.
     ***
     *  @fn void AudioPlayer::clearSlotFilter(size_t slot)
     *  @brief Clears the filter attached to a slot
     *  
     *  Assert/undefined behavior when the slot parameter is higher than three.
     *  @param slot Index of the slot to clear.
     ***/
}
