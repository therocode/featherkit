#include <featherkit/audio/audiofilestream.hpp>
#include <iostream>

namespace fea
{
    AudioFileStream::AudioFileStream() :
        mBufferSize(48000)
    {
    }

    void AudioFileStream::fillBufferData(size_t bufferIndex, AudioData& toFill)
    {
        toFill.mSamples.resize(mBufferSize);
        toFill.mSampleAmount = 0;

        size_t sampleIndex = bufferIndex * mBufferSize / (sizeof(int16_t) * mChannelCount);
        sf_seek(mFile.getInternal(), sampleIndex, SEEK_SET);

        size_t readAmount = static_cast<std::size_t>(sf_read_short(mFile.getInternal(), toFill.mSamples.data(), mBufferSize / (sizeof(int16_t))));
        toFill.mSampleAmount = readAmount;
    }

    void AudioFileStream::openFile(const std::string& path)
    {
        mFile.open(path);
        setStreamProperties(mFile.getChannelCount(), mFile.getSampleRate());
        reset();
    }
}
