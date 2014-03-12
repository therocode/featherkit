#include <featherkit/audio/audiofilestream.hpp>
#include <iostream>

namespace fea
{
    AudioFileStream::AudioFileStream()
    {
    }

    void AudioFileStream::fillBufferData(size_t bufferIndex, AudioData& toFill)
    {
        size_t sampleAmount = toFill.mSamples.size();

        size_t sampleIndex = bufferIndex * sampleAmount / mChannelCount;
        sf_seek(mFile.getInternal(), sampleIndex, SEEK_SET);

        size_t readAmount = static_cast<std::size_t>(sf_read_short(mFile.getInternal(), toFill.mSamples.data(), sampleAmount));
        toFill.mSampleAmount = readAmount;
    }

    void AudioFileStream::openFile(const std::string& path)
    {
        mFile.open(path);
        setStreamProperties(mFile.getChannelCount(), mFile.getSampleRate());
        reset();
    }
}
