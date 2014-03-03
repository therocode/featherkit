#include <featherkit/audio/audiosource.hpp>
            
namespace fea
{
    const AudioBufferList& AudioSource::getBuffers() const
    {
        return mBuffers;
    }
}
