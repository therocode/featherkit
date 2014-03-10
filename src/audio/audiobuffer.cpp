#include <featherkit/audio/audiobuffer.hpp>
#include <utility>

namespace fea
{
    AudioBuffer::AudioBuffer() : mDataSize(0)
    {
        alGenBuffers(1, &mBufferId);
    }
    
    AudioBuffer::AudioBuffer(AudioBuffer&& other) : 
        mBufferId(0),
        mDataSize(0)
    {
        std::swap(mBufferId, other.mBufferId);
        std::swap(mDataSize, other.mDataSize);
    }

    AudioBuffer& AudioBuffer::operator=(AudioBuffer&& other)
    {
        std::swap(mBufferId, other.mBufferId);
        std::swap(mDataSize, other.mDataSize);
        
        return *this;
    }

    AudioBuffer::~AudioBuffer()
    {
        if(mBufferId != 0)
            alDeleteBuffers(1, &mBufferId);
    }
    
    ALuint AudioBuffer::getBufferId() const
    {
        return mBufferId;
    }
}
