#include <featherkit/audio/audiostream.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    AudioStream::AudioStream() : 
        mBufferSize(48000),
        mNextToFill(0),
        mFormat(0),
        mChannelCount(0),
        mSampleRate(0),
        mLooping(false)
    {
        size_t bufferAmount = 3;

        for(size_t i = 0; i < bufferAmount; i++)
        {
            mBuffers.push_back(AudioBuffer());
        }
    }

    AudioStream::AudioStream(size_t bufferAmount, size_t bufferSize) : 
        mBufferSize(bufferSize),
        mNextToFill(0),
        mFormat(0),
        mChannelCount(0),
        mSampleRate(0),
        mLooping(false)
    {
        for(size_t i = 0; i < bufferAmount; i++)
        {
            mBuffers.push_back(AudioBuffer());
        }
    }
    
    void AudioStream::setStreamProperties(size_t channelCount, size_t sampleRate)
    {
        mSampleRate = sampleRate;
        mChannelCount = channelCount;

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
    }

    AudioBuffer* AudioStream::nextReadyBuffer()
    {
        if(mReadyBuffers.size() > 0)
        {
            size_t index = mReadyBuffers.front();
            mReadyBuffers.pop();
            mConsumingBuffers.push(index);
            return &mBuffers[index];
        }
        else
        {
            return nullptr;
        }
    }

    void AudioStream::bufferConsumed()
    {
        FEA_ASSERT(mConsumingBuffers.size() != 0, "Cannot notify AudioStream that a buffer has been consumed when no buffers have been fetched for consumption!");
        size_t consumed = mConsumingBuffers.front();
        mConsumingBuffers.pop();

        size_t filled = fillBuffer(&mBuffers[consumed]);
        
        if(filled > 0)
        {
            mReadyBuffers.push(consumed); 
        }
        else
        {
            if(mLooping)
            {
                mNextToFill = 0;

                filled = fillBuffer(&mBuffers[consumed]);

                if(filled > 0)
                {
                    mReadyBuffers.push(consumed); 
                }
            }
        }
    }
            
    size_t AudioStream::getSampleRate() const
    {
        return mSampleRate;
    }
    
    size_t AudioStream::fillBuffer(AudioBuffer* buffer)
    {
        AudioData audioData;
        audioData.mSamples.resize(mBufferSize);
        audioData.mSampleAmount = 0;

        fillBufferData(mNextToFill, audioData);
        mNextToFill++;

        if(audioData.mSampleAmount > 0)
        {
            alBufferData(buffer->getBufferId(), mFormat, audioData.mSamples.data(), audioData.mSampleAmount * sizeof(int16_t), mSampleRate);
        }
        
        return audioData.mSampleAmount;
    }
    
    void AudioStream::reset()
    {
        mReadyBuffers = std::queue<size_t>();
        mConsumingBuffers = std::queue<size_t>();
        mNextToFill = 0;

        for(size_t i = 0; i < mBuffers.size(); i++)
        {
            size_t filled = fillBuffer(&mBuffers[i]);

            if(filled > 0)
                mReadyBuffers.push(i);
        }
    }
    
    void AudioStream::setLooping(bool loop)
    {
        mLooping = loop;
    }
}
