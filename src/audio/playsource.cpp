#include <featherkit/audio/playsource.h>
#include <utility>

namespace fea
{
    PlaySource::PlaySource()
    {
        alGenSources(1, &mSourceId);
    }
    
    PlaySource::PlaySource(PlaySource&& other)
    {
        alGenSources(1, &mSourceId);
        std::swap(mSourceId, other.mSourceId);
    }

    PlaySource& PlaySource::operator=(PlaySource&& other)
    {
        std::swap(mSourceId, other.mSourceId);
        
        return *this;
    }

    PlaySource::~PlaySource()
    {
        alDeleteSources(1, &mSourceId);
    }
    
    ALuint PlaySource::getSourceId() const
    {
        return mSourceId;
    }
}
