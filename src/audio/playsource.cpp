#include <featherkit/audio/playsource.hpp>
#include <utility>
#include <iostream>

namespace fea
{
    PlaySource::PlaySource()
    {
        std::cout << "constructing. before, the id is " << mSourceId << "\n";
        alGenSources(1, &mSourceId);
        std::cout << "after, the id is " << mSourceId << "\n";
    }
    
    PlaySource::PlaySource(PlaySource&& other) :
        mSourceId(0)
    {
        std::cout << "before move: this: " << mSourceId << " other: " << other.mSourceId << "\n";
        std::swap(mSourceId, other.mSourceId);
        std::cout << "after move: this: " << mSourceId << " other: " << other.mSourceId << "\n";
    }

    PlaySource& PlaySource::operator=(PlaySource&& other)
    {
        std::cout << "before amove: this: " << mSourceId << " other: " << other.mSourceId << "\n";
        std::swap(mSourceId, other.mSourceId);
        std::cout << "before amove: this: " << mSourceId << " other: " << other.mSourceId << "\n";
        
        return *this;
    }

    PlaySource::~PlaySource()
    {
        std::cout << "destroying with id " << mSourceId << "\n";
        if(mSourceId != 0)
            alDeleteSources(1, &mSourceId);
    }
    
    ALuint PlaySource::getSourceId() const
    {
        return mSourceId;
    }
}
