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
        std::cout << "filling buffer index " << bufferIndex << "\n";
        AudioData sampleData;
        sampleData.mDataAmount = 0;

        size_t sampleIndex = bufferIndex * mBufferSize / (sizeof(int16_t) * mChannelCount);
        sf_seek(mFile->getInternal(), sampleIndex, SEEK_SET);

        std::shared_ptr<int16_t> data(new int16_t [mBufferSize], [](int16_t* arr) { delete [] arr; });

        sampleData.mData = std::static_pointer_cast<void>(data);

        size_t readAmount = static_cast<std::size_t>(sf_read_short(mFile->getInternal(), data.get(), mBufferSize / (sizeof(int16_t))));
        sampleData.mDataAmount = readAmount * sizeof(int16_t);

        return sampleData;
    }

    void AudioFileStream::setFile(AudioFile& file)
    {
        mFile = &file;
        setStreamProperties(file.getChannelCount(), file.getSampleRate());
        reset();
    }
}
