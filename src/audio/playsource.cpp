#include <featherkit/audio/playsource.hpp>
#include <utility>
#include <iostream>

namespace fea
{
    PlaySource::PlaySource()
    {
        alGenSources(1, &mSourceId);
    }
    
    PlaySource::PlaySource(PlaySource&& other) :
        mSourceId(0)
    {
        std::swap(mSourceId, other.mSourceId);
    }

    PlaySource& PlaySource::operator=(PlaySource&& other)
    {
        std::swap(mSourceId, other.mSourceId);
        
        return *this;
    }

    PlaySource::~PlaySource()
    {
        if(mSourceId != 0)
            alDeleteSources(1, &mSourceId);
    }
    
    ALuint PlaySource::getSourceId() const
    {
        return mSourceId;
    }
}
