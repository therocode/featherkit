#include <fea/audio/audiofilestream.hpp>
#include <iostream>

namespace fea
{
    AudioFileStream::AudioFileStream()
    {
    }

    void AudioFileStream::fillBufferData(size_t sampleIndex, std::vector<int16_t>& toFill)
    {
        size_t desiredSampleAmount = toFill.size();

        mFile.fillBufferFromIndex(toFill, sampleIndex);
    }

    void AudioFileStream::openFile(const std::string& path)
    {
        mFile.open(path);
        setStreamProperties(mFile.getChannelCount(), mFile.getSampleRate());
        reset();
    }
}
