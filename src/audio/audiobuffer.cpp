#include <featherkit/audio/audiobuffer.h>
#include <utility>

namespace fea
{
    AudioBuffer::AudioBuffer() : mDataSize(0)
    {
        alGenBuffers(1, &mBufferId);
    }
    
    AudioBuffer::AudioBuffer(AudioBuffer&& other) : mDataSize(0)
    {
        alGenBuffers(1, &mBufferId);
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
        alDeleteBuffers(1, &mBufferId);
    }
    
    ALuint AudioBuffer::getBufferId() const
    {
        return mBufferId;
    }
}
