#include <featherkit/audio/audiofile.hpp>
#include <featherkit/audio/audiofilenotfoundexception.hpp>
#include <featherkit/assert.hpp>
#include <iostream>

namespace fea
{
    AudioFile::AudioFile() : mFile(nullptr), mChannelCount(0), mSampleRate(0), mSampleAmount(0)
    {
    }
    
    AudioFile::AudioFile(AudioFile&& other)  : mFile(nullptr), mChannelCount(0), mSampleRate(0), mSampleAmount(0)
    {
        std::swap(mFile, other.mFile);
        std::swap(mChannelCount, other.mChannelCount);
        std::swap(mSampleRate, other.mSampleRate);
        std::swap(mSampleAmount, other.mSampleAmount);
    }

    AudioFile& AudioFile::operator=(AudioFile&& other)
    {
        std::swap(mFile, other.mFile);
        std::swap(mChannelCount, other.mChannelCount);
        std::swap(mSampleRate, other.mSampleRate);
        std::swap(mSampleAmount, other.mSampleAmount);
        
        return *this;
    }
    
    AudioFile::~AudioFile()
    {
        if(mFile)
        {
            sf_close(mFile);
        }
    }

    int32_t AudioFile::getChannelCount() const
    {
        return mChannelCount;
    }

    int32_t AudioFile::getSampleRate() const
    {
        return mSampleRate;
    }

    std::vector<int16_t> AudioFile::getSampleData() const
    {
        if(mSampleAmount == 0)
            return std::vector<int16_t>();

        std::vector<int16_t> sampleData(mSampleAmount);

        size_t readAmount = static_cast<std::size_t>(sf_read_short(mFile, sampleData.data(), mSampleAmount));
        sampleData.resize(readAmount);

        sf_seek(mFile, 0, 0);

        return sampleData;
    }

    void AudioFile::open(const std::string& path)
    {
        if(mFile)
        {
            sf_close(mFile);
        }

        SF_INFO fileInfo;
        mFile = sf_open(path.c_str(), SFM_READ, &fileInfo);

        if(mFile == nullptr)
        {
            throw AudioFileNotFoundException("Error when trying to load audio file '" + path + "!");
        }

        mChannelCount = fileInfo.channels;
        mSampleRate = fileInfo.samplerate;
        mSampleAmount = static_cast<std::size_t>(fileInfo.frames) * fileInfo.channels;
    }
    
    void AudioFile::fillBufferFromIndex(std::vector<int16_t>& buffer, size_t sampleIndex)
    {
        FEA_ASSERT(mFile != nullptr, "Cannot fill buffer when no valid file is loaded!");

        sf_seek(mFile, sampleIndex / mChannelCount, SEEK_SET);
         
        size_t readAmount = static_cast<std::size_t>(sf_read_short(mFile, buffer.data(), buffer.size()));
        buffer.resize(readAmount);
    }
}
