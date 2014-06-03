#pragma once
#include <fea/config.hpp>
#include <fea/audio/openal.hpp>

namespace fea
{
    class FEA_API AudioEffect
    {
        public:
            AudioEffect();
            AudioEffect(const AudioEffect& other) = delete;
            AudioEffect(AudioEffect&& other);
            AudioEffect& operator=(const AudioEffect& other) = delete;
            AudioEffect& operator=(AudioEffect&& other);
            ~AudioEffect();
            ALuint getEffectId() const;
            void setEffectGain(float gain);
            float getEffectGain() const;
            void setAutoAdjustments(bool enabled);
            bool getAutoAdjustments() const;
        private:
            ALuint mEffectId;
            float mGain;
            bool mAutoSend;
    };
    /** @addtogroup Audio
     *@{
     *  @class AudioEffect
     *@}
     ***
     *  @class AudioEffect
     *  @brief Base class for EFX based effects
     *
     *  Effects can be added to slots in the AudioPlayer class. When an audio source sends audio to the effect slot an effect has been added to, the effect is applied.
     *
     *  All the effects are based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and are hence not documented here. So have a look there to find out all about what the effects are, and what default values they have and which values they expect.
     ***
     *  @fn AudioEffect::AudioEffect()
     *  @brief Construct an AudioEffect. 
     ***
     *  @fn AudioEffect::AudioEffect(const AudioEffect& other) = delete
     *  @brief Deleted copy constructor.
     ***
     *  @fn AudioEffect::AudioEffect(AudioEffect&& other)
     *  @brief Move an AudioEffect.
     ***
     *  @fn AudioEffect& AudioEffect::operator=(const AudioEffect& other) = delete
     *  @brief Deleted assignment operator.
     ***
     *  @fn AudioEffect& AudioEffect::operator=(AudioEffect&& other)
     *  @brief Move an AudioEffect.
     ***
     *  @fn AudioEffect::~AudioEffect()
     *  @brief Destroy an AudioEffect.
     ***
     *  @fn ALuint AudioEffect::getEffectId() const
     *  @brief Get the internal OpenAL Id.
     *  @return The id.
     ***
     *  @fn void AudioEffect::setEffectGain(float gain)
     *  @brief Set the gain of the effect.
     *
     *  Setting this will cause a change in the output volume of the effect applied on sources that send to it. The default is 1.0f and the total output will be capped at 1.0f. 
     *  Assert/undefined behavior if the input is less than zero.
     *  @param gain Gain.
     ***
     *  @fn float AudioEffect::getEffectGain() const
     *  @brief Get the gain of the effect.
     *  @return The gain.
     ***
     *  @fn void AudioEffect::setAutoAdjustments(bool enabled)
     *  @brief Set auto adjustments.
     *
     *  This property is used to enable or disable automatic send adjustments based on the physical positions of the sources and the listener. 
     *  It should be enabled when an application wishes to use a reverb effect to simulate the environment surrounding a listener or a collection of Sources. Default is to be on.
     *  @param enabled True if it should be on.
     ***
     *  @fn bool AudioEffect::getAutoAdjustments() const
     *  @brief Check if auto adjustments are on.
     *  @return True if it is on.
     ***/
}
