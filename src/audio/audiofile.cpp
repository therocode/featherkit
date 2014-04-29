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
            ov_clear(mFile);
            delete mFile;
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

        ov_raw_seek(mFile, 0);

        int64_t read = 0;
        int64_t totalRead = 0;
        int bitstream = 0;


        while((read = ov_read(mFile, ((char*)sampleData.data()) + totalRead, (mSampleAmount * 2) - totalRead, 0, 2, 1, &bitstream)))
        {
            if(read < 0)
            {
                break;
            }

            totalRead += read;
        }

        sampleData.resize(totalRead / 2);

        return sampleData;
    }

    void AudioFile::open(const std::string& path)
    {
        if(mFile)
        {
            ov_clear(mFile);
            delete mFile;
        }

        mFile = new OggVorbis_File;

        if(ov_fopen(path.c_str(), mFile))
        {
            throw AudioFileNotFoundException("Error when trying to load audio file '" + path + "!");
        }

        vorbis_info* info = ov_info(mFile, -1);

        mChannelCount = info->channels;
        mSampleRate = info->rate;
        mSampleAmount = 2 * ov_pcm_total(mFile, -1);
    }
    
    void AudioFile::fillBufferFromIndex(std::vector<int16_t>& buffer, size_t sampleIndex)
    {
        FEA_ASSERT(mFile != nullptr, "Cannot fill buffer when no valid file is loaded!");

        ov_pcm_seek(mFile, sampleIndex / mChannelCount);
         
        int64_t read = 0;
        int64_t totalRead = 0;
        int bitstream = 0;

        while((read = ov_read(mFile, ((char*)buffer.data()) + totalRead, (buffer.size() * 2) - totalRead, 0, 2, 1, &bitstream)))
        {
            if(read < 0)
            {
                break;
            }

            totalRead += read;
        }

        buffer.resize(totalRead / 2);
    }
}
