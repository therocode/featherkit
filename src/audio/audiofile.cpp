#include <featherkit/audio/audiofile.hpp>
#include <featherkit/util/filenotfoundexception.hpp>
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

    AudioData AudioFile::getSampleData() const
    {
        if(mSampleAmount == 0)
            return AudioData();

        std::shared_ptr<int16_t> data(new int16_t [mSampleAmount * sizeof(int16_t)], [](int16_t* arr) { delete [] arr; });

        AudioData sampleData;
        sampleData.mData = std::static_pointer_cast<void>(data);

        size_t readAmount = static_cast<std::size_t>(sf_read_short(mFile, data.get(), mSampleAmount));
        sampleData.mDataAmount = readAmount * sizeof(int16_t);

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
            throw util::FileNotFoundException("Error when trying to load audio file '" + path + "!");
        }

        mChannelCount = fileInfo.channels;
        mSampleRate = fileInfo.samplerate;
        mSampleAmount = static_cast<std::size_t>(fileInfo.frames) * fileInfo.channels;
    }
    
    SNDFILE* AudioFile::getInternal()
    {
        return mFile;
    }
}
