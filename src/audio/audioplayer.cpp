#include <featherkit/audio/audioplayer.h>
#include <featherkit/assert.h>
            
namespace fea
{
    AudioPlayer::AudioPlayer()
    {
        mAudioDevice = alcOpenDevice(nullptr);

        FEA_ASSERT(mAudioDevice, "Error! Failed to create an OpenAL device!");

        mAudioContext = alcCreateContext(mAudioDevice, nullptr);

        FEA_ASSERT(mAudioContext, "Error! Failed to create an OpenAL context!");
            
        alcMakeContextCurrent(mAudioContext);
    }
    
    AudioPlayer::~AudioPlayer()
    {
        alcMakeContextCurrent(nullptr);
        if(mAudioContext)
            alcDestroyContext(mAudioContext);

        if(mAudioDevice)
            alcCloseDevice(mAudioDevice);
    }

    void AudioPlayer::play(Audio& audio)
    {
    }
}
