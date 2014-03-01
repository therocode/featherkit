#include <featherkit/audio/audiobuffer.h>

namespace fea
{
    AudioBuffer::AudioBuffer() : mDataSize(0)
    {
        alGenBuffers(1, &mBufferId);
    }

    AudioBuffer::~AudioBuffer()
    {
        alDeleteBuffers(1, &mBufferId);
    }
}
