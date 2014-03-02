#include <featherkit/audio/audioplayer.h>
#include <featherkit/audio/audiosource.h>
#include <featherkit/audio/audio.h>
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

        alGenSources(1, &source);
    }
    
    AudioPlayer::~AudioPlayer()
    {
        alcMakeContextCurrent(nullptr);
        if(mAudioContext)
            alcDestroyContext(mAudioContext);

        if(mAudioDevice)
            alcCloseDevice(mAudioDevice);

        alDeleteSources(1, &source);
    }

    void AudioPlayer::play(Audio& audio)
    {
        const fea::AudioBufferList& buffers = audio.getSource().getBuffers();

        if(buffers.size() == 1)
        {
            //single source
            std::cout << "hej\n";
            alSourcei(source, AL_BUFFER, buffers[0]->getBufferId());
            alSourcePlay(source);
        }
        else if(buffers.size() > 1)
        {
            //streamed source
        }
    }
}
