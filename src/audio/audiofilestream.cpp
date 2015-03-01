#include <fea/audio/audiofilestream.hpp>

namespace fea
{
    AudioFileStream::AudioFileStream()
    {
    }

    void AudioFileStream::fillBufferData(size_t sampleIndex, std::vector<int16_t>& toFill)
    {
        mFile.fillBufferFromIndex(toFill, sampleIndex);
    }

    void AudioFileStream::openFile(const std::string& path)
    {
        mFile.open(path);
        setStreamProperties(mFile.getChannelCount(), mFile.getSampleRate());
        reset();
    }
}
