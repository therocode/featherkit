#include <featherkit/audio/audioplayer.h>
#include <featherkit/audio/audiosource.h>
#include <featherkit/audio/audio.h>
#include <featherkit/assert.h>
            
namespace fea
{
    AudioPlayer::AudioPlayer() : mMaxSoundsPlaying(32), mNumSoundsPlaying(0), mNextHandle(0)
    {
        mAudioDevice = alcOpenDevice(nullptr);

        FEA_ASSERT(mAudioDevice, "Error! Failed to create an OpenAL device!");

        mAudioContext = alcCreateContext(mAudioDevice, nullptr);

        FEA_ASSERT(mAudioContext, "Error! Failed to create an OpenAL context!");
            
        alcMakeContextCurrent(mAudioContext);

        setupSources(mMaxSoundsPlaying);
    }
    
    AudioPlayer::~AudioPlayer()
    {
        alcMakeContextCurrent(nullptr);
        if(mAudioContext)
            alcDestroyContext(mAudioContext);

        if(mAudioDevice)
            alcCloseDevice(mAudioDevice);
    }

    AudioHandle AudioPlayer::play(Audio& audio)
    {
        const fea::AudioBufferList& buffers = audio.getSource().getBuffers();

        //single source
        if(buffers.size() == 1)
        {
            PlaySource source = std::move(mSources.top());
            mSources.pop();

            alSourcei(source.getSourceId(), AL_BUFFER, buffers[0]->getBufferId());
            alSourcePlay(source.getSourceId());

            size_t handle = mNextHandle;
            mNextHandle++;
            mPlayingSources.emplace(handle, std::move(source));
            return handle;
        }
        //streamed source
        else if(buffers.size() > 1)
        {
            return 0;
        }
        return 0;
    }
    
    size_t AudioPlayer::getMaxSoundsPlaying() const
    {
        return mMaxSoundsPlaying;
    }
    
    size_t AudioPlayer::getNumSoundsPlaying() const
    {
        return mNumSoundsPlaying;
    }
    
    void AudioPlayer::setupSources(size_t maxSoundAmount)
    {
        for(size_t i = 0; i < maxSoundAmount; i++)
            mSources.push(PlaySource());
    }

    void AudioPlayer::pause(AudioHandle handle)
    {
        auto source = mPlayingSources.find(handle);

        if(source != mPlayingSources.end())
        {
            alSourcePause(source->second.getSourceId());
        }
    }

    void AudioPlayer::resume(AudioHandle handle)
    {
        auto source = mPlayingSources.find(handle);

        if(source != mPlayingSources.end())
        {
            alSourcePlay(source->second.getSourceId());
        }
    }

    void AudioPlayer::stop(AudioHandle handle)
    {
        auto source = mPlayingSources.find(handle);

        if(source != mPlayingSources.end())
        {
            alSourceStop(source->second.getSourceId());
        }
    }
}
