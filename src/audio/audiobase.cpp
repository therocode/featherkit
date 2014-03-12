#include <featherkit/audio/audiobase.hpp>

namespace fea
{
    AudioBase::AudioBase() : 
        mLooping(false),
        mOffset(0)
    {
    }

    void AudioBase::setLooping(bool loop)
    {
        mLooping = loop;
    }

    bool AudioBase::getLooping() const
    {
        return mLooping;
    }

    void AudioBase::setPlayOffset(std::chrono::milliseconds timePoint)
    {
        mOffset = timePoint;
    }

    std::chrono::milliseconds AudioBase::getPlayOffset() const
    {
        return mOffset;
    }
}
