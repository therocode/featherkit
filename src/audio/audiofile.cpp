#include <featherkit/audio/audiofile.h>
#include <featherkit/util/filenotfoundexception.h>
#include <iostream>

namespace fea
{
    AudioFile::AudioFile() : mFile(nullptr), mFormat(0), mSampleRate(0), mSampleAmount(0)
    {
    }
    
    AudioFile::AudioFile(AudioFile&& other)  : mFile(nullptr), mFormat(0), mSampleRate(0), mSampleAmount(0)
    {
        std::swap(mFile, other.mFile);
        std::swap(mFormat, other.mFormat);
        std::swap(mSampleRate, other.mSampleRate);
        std::swap(mSampleAmount, other.mSampleAmount);
    }

    AudioFile& AudioFile::operator=(AudioFile&& other)
    {
        std::swap(mFile, other.mFile);
        std::swap(mFormat, other.mFormat);
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

    ALenum AudioFile::getFormat() const
    {
        return mFormat;
    }

    ALint AudioFile::getSampleRate() const
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

        int32_t channelCount = fileInfo.channels;
        mSampleRate = fileInfo.samplerate;
        mSampleAmount = static_cast<std::size_t>(fileInfo.frames) * fileInfo.channels;
        
        switch (channelCount)
        {
            case 1  : mFormat = AL_FORMAT_MONO16;                    break;
            case 2  : mFormat = AL_FORMAT_STEREO16;                  break;
            case 4  : mFormat = alGetEnumValue("AL_FORMAT_QUAD16");  break;
            case 6  : mFormat = alGetEnumValue("AL_FORMAT_51CHN16"); break;
            case 7  : mFormat = alGetEnumValue("AL_FORMAT_61CHN16"); break;
            case 8  : mFormat = alGetEnumValue("AL_FORMAT_71CHN16"); break;
            default : mFormat = 0;                                   break;
        }

        // Fixes a bug on OS X supposedly
        if (mFormat == -1)
            mFormat = 0;
    }
}
