#include <featherkit/audio/audioplayer.h>
#include <featherkit/audio/audiosource.h>
#include <featherkit/audio/audio.h>
#include <featherkit/assert.h>
            
namespace fea
{
    AudioPlayer::AudioPlayer() : mMaxSoundsPlaying(32), mNumSoundsPlaying(0), mNextHandle(0), mRenewer(&AudioPlayer::renewerThread, this), mRenewSources(true)
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
        mRenewSources = false;
        mRenewer.join();

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
            std::lock_guard<std::mutex> lock(mSourcesMutex);

            PlaySource source = std::move(mIdleSources.top());
            mIdleSources.pop();

            
            ALuint sourceId = source.getSourceId();
            alSourcei(sourceId, AL_BUFFER, buffers[0]->getBufferId()); //set buffer

            auto position = audio.getPosition();
            alSource3f(sourceId, AL_POSITION, position.x, position.y, position.z); //set position

            alSourcePlay(sourceId); //play

            size_t handle = mNextHandle;
            mNextHandle++;
            mPlayingSources.emplace(handle, std::move(source));
            mNumSoundsPlaying++;
            return handle;
        }
        //streamed source
        else if(buffers.size() > 1)
        {
            return 0;
        }
        return 0;
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
    
    size_t AudioPlayer::getMaxSoundsPlaying() const
    {
        return mMaxSoundsPlaying;
    }
    
    size_t AudioPlayer::getNumSoundsPlaying() const
    {
        return mNumSoundsPlaying;
    }
    
    PlayStatus AudioPlayer::getStatus(AudioHandle handle) const
    {
        auto sourceIterator = mPlayingSources.find(handle);

        if(sourceIterator != mPlayingSources.end())
        {
            ALint state;
            alGetSourcei(sourceIterator->second.getSourceId(), AL_SOURCE_STATE, &state);

            if(state == AL_PLAYING)
                return PLAYING;
            else if(state == AL_PAUSED)
                return PAUSED;
            else
                return EXPIRED;
        }
        else
        {
            return EXPIRED;
        }
    }

    void AudioPlayer::setPosition(AudioHandle handle, const Vec3F& position) const
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set position on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        alSource3f(source.getSourceId(), AL_POSITION, position.x, position.y, position.z);
    }

    Vec3F AudioPlayer::getPosition(AudioHandle handle)
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get position of an expired audio!");
        auto& source = mPlayingSources.at(handle);

        Vec3F position;
        alGetSource3f(source.getSourceId(), AL_POSITION, &position.x, &position.y, &position.z);
        return position;
    }
    
    void AudioPlayer::setupSources(size_t maxSoundAmount)
    {
        for(size_t i = 0; i < maxSoundAmount; i++)
            mIdleSources.push(PlaySource());
    }
    
    void AudioPlayer::renewerThread()
    {
        while(mRenewSources)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            renewFinishedSources();
        }
    }

    void AudioPlayer::renewFinishedSources()
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        
        for(auto sourceIterator = mPlayingSources.begin(); sourceIterator != mPlayingSources.end();)
        {
            ALint state;
            alGetSourcei(sourceIterator->second.getSourceId(), AL_SOURCE_STATE, &state);
            if(state == AL_STOPPED)
            {
                mIdleSources.push(std::move(sourceIterator->second));
                sourceIterator = mPlayingSources.erase(sourceIterator);
                mNumSoundsPlaying--;
            }
            else
            {
                sourceIterator++;
            }
        }
    }
}
