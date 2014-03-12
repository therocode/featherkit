#include <featherkit/audio/audiofilestream.hpp>
#include <iostream>

namespace fea
{
    AudioFileStream::AudioFileStream() :
        mBufferSize(48000)
    {
    }

    AudioData AudioFileStream::fetchBufferData(size_t bufferIndex)
    {
        AudioData sampleData;
        sampleData.mSamples.resize(mBufferSize);
        sampleData.mSampleAmount = 0;

        size_t sampleIndex = bufferIndex * mBufferSize / (sizeof(int16_t) * mChannelCount);
        sf_seek(mFile->getInternal(), sampleIndex, SEEK_SET);

        size_t readAmount = static_cast<std::size_t>(sf_read_short(mFile->getInternal(), sampleData.mSamples.data(), mBufferSize / (sizeof(int16_t))));
        sampleData.mSampleAmount = readAmount;

        return sampleData;
    }

    void AudioFileStream::setFile(AudioFile& file)
    {
        mFile = &file;
        setStreamProperties(file.getChannelCount(), file.getSampleRate());
        reset();
    }
}
