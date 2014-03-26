#pragma once
#include <featherkit/audio/audiostream.hpp>
#include <featherkit/audio/audiofile.hpp>

namespace fea
{
    class AudioFileStream : public AudioStream
    {
        public:
            AudioFileStream();
            virtual void fillBufferData(size_t sampleIndex, std::vector<int16_t>& toFill) override;
            void openFile(const std::string& path);
        private:
            AudioFile mFile;
    };
    /** @addtogroup Audio
     *@{
     *  @class AudioFileStream
     *@}
     ***
     *  @class AudioFileStream
     *  @brief Streams audio from a file.
     *
     *  This class inherits AudioStream and does not keep much data in memory. This makes it ideal for playing music and other big audio files.
     ***
     *  @fn AudioFileStream::AudioFileStream()
     *  @brief Construct an AudioFileStream. 
     ***
     *  @fn void AudioFileStream::openFile(const std::string& path)
     *  @brief Open an audio file for streaming.
     *
     *  If the file is valid, the stream is ready to be played after this function is called. Will throw an AudioFileNotFoundException if a file is not found.
     ***/
}
