#include <featherkit/audio/audiosource.h>
            
namespace fea
{
    const AudioBufferList& AudioSource::getBuffers() const
    {
        return mBuffers;
    }
}
