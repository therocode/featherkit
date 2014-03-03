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

            auto velocity = audio.getVelocity();
            alSource3f(sourceId, AL_VELOCITY, velocity.x, velocity.y, velocity.z); //set velocity

            alSourcef(sourceId, AL_PITCH, audio.getPitch()); //set pitch

            alSourcef(sourceId, AL_GAIN, audio.getGain()); //set gain

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

    void AudioPlayer::setVelocity(AudioHandle handle, const Vec3F& velocity) const
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set velocity on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        alSource3f(source.getSourceId(), AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    }

    Vec3F AudioPlayer::getVelocity(AudioHandle handle)
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get velocity of an expired audio!");
        auto& source = mPlayingSources.at(handle);

        Vec3F velocity;
        alGetSource3f(source.getSourceId(), AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
        return velocity;
    }

    void AudioPlayer::setPitch(AudioHandle handle, float pitch) const
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set pitch on an expired audio!");
        FEA_ASSERT(pitch > 0.0f, "Trying to set pitch to 0 or less! Given " + std::to_string(pitch));
        auto& source = mPlayingSources.at(handle);
        
        alSourcef(source.getSourceId(), AL_PITCH, pitch);
    }

    float AudioPlayer::getPitch(AudioHandle handle)
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get pitch on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float pitch;
        alGetSourcef(source.getSourceId(), AL_PITCH, &pitch);
        return pitch;
    }

    void AudioPlayer::setGain(AudioHandle handle, float gain) const
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set gain on an expired audio!");
        FEA_ASSERT(gain > 0.0f, "Trying to set gain to 0 or less! Given " + std::to_string(gain));
        auto& source = mPlayingSources.at(handle);
        
        alSourcef(source.getSourceId(), AL_GAIN, gain);
    }

    float AudioPlayer::getGain(AudioHandle handle)
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get gain on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float gain;
        alGetSourcef(source.getSourceId(), AL_GAIN, &gain);
        return gain;
    }

    void AudioPlayer::setAttenuationFactor(AudioHandle handle, float attenuationFactor)
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set attenuation factor on an expired audio!");
        FEA_ASSERT(attenuationFactor > 0.0f, "Trying to set attenuation factor to 0 or less! Given " + std::to_string(attenuationFactor));
        auto& source = mPlayingSources.at(handle);

        alSourcef(source.getSourceId(), AL_ROLLOFF_FACTOR, attenuationFactor);
    }

    float AudioPlayer::getAttenuationFactor(AudioHandle handle) const
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get attenuation factor on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float attenuationFactor;
        alGetSourcef(source.getSourceId(), AL_ROLLOFF_FACTOR, &attenuationFactor);
        return attenuationFactor;
    }

    void AudioPlayer::setAttenuationDistance(AudioHandle handle, float attenuationDistance)
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set attenuation distance on an expired audio!");
        FEA_ASSERT(attenuationDistance > 0.0f, "Trying to set attenuation factor to 0 or less! Given " + std::to_string(attenuationDistance));
        auto& source = mPlayingSources.at(handle);

        alSourcef(source.getSourceId(), AL_REFERENCE_DISTANCE, attenuationDistance);
    }

    float AudioPlayer::getAttenuationDistance(AudioHandle handle) const
    {
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get attenuation distance on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float attenuationDistance;
        alGetSourcef(source.getSourceId(), AL_REFERENCE_DISTANCE, &attenuationDistance);
        return attenuationDistance;
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
