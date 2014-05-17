#pragma once
#include <memory>
#include <fea/audio/audiobuffer.hpp>

namespace fea
{
    class AudioFile;

    class AudioSample
    {
        public:
            void loadSampleData(const AudioFile& audioFile);
            const AudioBuffer& getBuffer() const;
        private:
            std::unique_ptr<AudioBuffer> mBuffer;
    };
    /** @addtogroup Audio
     *@{
     *  @class AudioSample
     *@}
     ***
     *  @class AudioSample
     *  @brief A sample is a container for audio data.
     *
     *  The data is used by Audio instances. AudioSample instances that are being used must be kept in a valid scope whilst in use.
     ***
     *  @fn void AudioSample::loadSampleData(const AudioFile& audioFile)
     *  @brief Load audio samples from an audio file.
     *
     *  The data will be stored internally and the AudioFile can be discarded afterwards.
     *  @param audioFile File to load samples from.
     ***
     *  @fn const AudioBuffer& AudioSample::getBuffer() const
     *  @brief Get the internal AudioBuffer.
     *  @return Audio buffer.
     ***/
}
