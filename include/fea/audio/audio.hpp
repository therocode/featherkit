#pragma once
#include <fea/config.hpp>
#include <fea/audio/audiobase.hpp>

namespace fea
{
    class AudioSample;

    class FEA_API Audio : public AudioBase
    {
        public:
            Audio();
            void setSample(AudioSample& sample);
            const AudioSample& getSample() const;
            bool hasSample() const;
        private:
            AudioSample* mSample;
    };

    /** @addtogroup Audio
     *@{
     *  @class Audio
     *@}
     ***
     *  @class Audio
     *  @brief Single sample based audio effect.
     *
     *  This class is used to play basic audio effects that are small enough to not stress the memory too much. For bigger files see AudioStream. The Audio class contains no actual audio data but needs an AudioSample to provide that. Multiple Audio instances can use the same AudioSample.
     ***
     *  @fn Audio::Audio()
     *  @brief Construct an Audio. 
     ***
     *  @fn void Audio::setSample(AudioSample& sample)
     *  @brief Set which sample to use.
     *
     *  The sample carries the actual audio data. Beware that the sample must not go out of scope whilst an audio is using it.
     *  @param sample Sample to use.
     ***
     *  @fn const AudioSample& Audio::getSample() const
     *  @brief Get the current sample in use.
     *
     *  Assert/undefined behavior when no sample is set. Check using hasSample.
     *  @return The current sample in use.
     ***
     *  @fn bool Audio::hasSample() const
     *  @brief Check if a sample is set.
     *  @return True if a sample is set.
     ***/
}
