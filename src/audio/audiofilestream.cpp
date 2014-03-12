#include <featherkit/audio/audiofilestream.hpp>
#include <iostream>

namespace fea
{
    AudioFileStream::AudioFileStream()
    {
    }

    void AudioFileStream::fillBufferData(size_t sampleIndex, AudioData& toFill)
    {
        size_t sampleAmount = toFill.mSamples.size();

        size_t fileSampleIndex = sampleIndex / mChannelCount;
        sf_seek(mFile.getInternal(), fileSampleIndex, SEEK_SET);

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
