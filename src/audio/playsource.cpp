#include <featherkit/audio/playsource.h>

namespace fea
{
    PlaySource::PlaySource()
    {
        alGenSources(1, &mSourceId);
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
