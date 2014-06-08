#include <fea/audio/audioplayer.hpp>
#include <fea/audio/audiosample.hpp>
#include <fea/audio/audio.hpp>
#include <fea/audio/audiostream.hpp>
#include <fea/audio/audiofilter.hpp>
#include <fea/assert.hpp>
#include <string>
#if !defined(FEA_NO_EFX)
#include "efx.h"
#endif

namespace fea
{
    AudioPlayer::AudioPlayer() : 
        mMaxSoundsPlaying(32), 
        mNumSoundsPlaying(0), 
        mNextHandle(1)
    {
        mAudioDevice = alcOpenDevice(nullptr);

        FEA_ASSERT(mAudioDevice, "Error! Failed to create an OpenAL device!");

        mAudioContext = alcCreateContext(mAudioDevice, nullptr);

        FEA_ASSERT(mAudioContext, "Error! Failed to create an OpenAL context!");
            
        alcMakeContextCurrent(mAudioContext);

        setupSources(mMaxSoundsPlaying);

#if !defined(FEA_NO_EFX)
        alcGetIntegerv(mAudioDevice, ALC_MAX_AUXILIARY_SENDS, 1, &mMaxAuxSend);

        for(size_t i = 0; i < 4; i++)
        {
            mEffectSlots.push_back(EffectSlot());
        }
#else
        mMaxAuxSend = 0;
#endif
    }
    
    AudioPlayer::~AudioPlayer()
    {
        for(auto& stream : mStreams)
            stream.second.stop();

        mStreams.clear();

        {
            std::lock_guard<std::mutex> lock(mSourcesMutex);

            std::vector<AudioHandle> playingSources;

            for(auto& source : mPlayingSources)
                playingSources.push_back(source.first);

            mIdleSources = std::stack<PlaySource>();
            mEffectSlots.clear();

            alcMakeContextCurrent(nullptr);
            if(mAudioContext)
                alcDestroyContext(mAudioContext);

            if(mAudioDevice)
                alcCloseDevice(mAudioDevice);
        }
    }

    AudioHandle AudioPlayer::play(Audio& audio)
    {
        renewFinishedSources();
        if(mNumSoundsPlaying == mMaxSoundsPlaying)
            return 0;

        FEA_ASSERT(audio.hasSample(), "Trying to play an audio with no sample set!");

        const AudioBuffer& buffer = audio.getSample().getBuffer();
        std::lock_guard<std::mutex> lock(mSourcesMutex);

        size_t handle = mNextHandle;
        mNextHandle++;
        mPlayingSources.emplace(handle, std::move(mIdleSources.top()));
        mIdleSources.pop();
        mNumSoundsPlaying++;

        ALuint sourceId = mPlayingSources.at(handle).getSourceId();
        alSourcei(sourceId, AL_BUFFER, buffer.getBufferId()); //set buffer

        auto position = audio.getPosition();
        alSource3f(sourceId, AL_POSITION, position.x, position.y, position.z); //set position

        auto velocity = audio.getVelocity();
        alSource3f(sourceId, AL_VELOCITY, velocity.x, velocity.y, velocity.z); //set velocity

        alSourcef(sourceId, AL_PITCH, audio.getPitch()); //set pitch

        alSourcef(sourceId, AL_GAIN, audio.getGain()); //set gain

        alSourcei(sourceId, AL_LOOPING, audio.isLooping() ? AL_TRUE : AL_FALSE); //set looping

        alSourcei(sourceId, AL_SOURCE_RELATIVE, audio.isRelative() ? AL_TRUE : AL_FALSE); //set relative

        alSourcef(sourceId, AL_SEC_OFFSET, static_cast<float>(audio.getPlayOffset().count()) / 1000.0f);//set offset

        const auto& effectSends = audio.getEffectSends();
        for(auto slotIndex : effectSends)
        {
#if !defined(FEA_NO_EFX)
            alSource3i(sourceId, AL_AUXILIARY_SEND_FILTER, mEffectSlots.at(slotIndex).getSlotId(), slotIndex, mEffectSlots.at(slotIndex).getFilter().getFilterId());
#endif
        }

        if(audio.hasFilter())
        {
#if !defined(FEA_NO_EFX)
            alSourcei(sourceId, AL_DIRECT_FILTER, audio.getFilter().getFilterId());
#endif
        }

        alSourcePlay(sourceId); //play


        return handle;
    }

    AudioHandle AudioPlayer::play(AudioStream& stream)
    {
        renewFinishedSources();
        if(mNumSoundsPlaying == mMaxSoundsPlaying)
             return 0;

        std::lock_guard<std::mutex> lock(mSourcesMutex);

        size_t handle = mNextHandle;
        mNextHandle++;
        mPlayingSources.emplace(handle, std::move(mIdleSources.top()));
        mIdleSources.pop();
        mNumSoundsPlaying++;

        stream.reset();

        ALuint sourceId = mPlayingSources.at(handle).getSourceId();

        auto position = stream.getPosition();
        alSource3f(sourceId, AL_POSITION, position.x, position.y, position.z); //set position

        auto velocity = stream.getVelocity();
        alSource3f(sourceId, AL_VELOCITY, velocity.x, velocity.y, velocity.z); //set velocity

        alSourcef(sourceId, AL_PITCH, stream.getPitch()); //set pitch

        alSourcef(sourceId, AL_GAIN, stream.getGain()); //set gain

        alSourcei(sourceId, AL_SOURCE_RELATIVE, stream.isRelative() ? AL_TRUE : AL_FALSE); //set relative

        const auto& effectSends = stream.getEffectSends();
        for(auto slotIndex : effectSends)
        {
#if !defined(FEA_NO_EFX)
            auto& effectSlot = mEffectSlots.at(slotIndex);
            alSource3i(sourceId, AL_AUXILIARY_SEND_FILTER, effectSlot.getSlotId(), slotIndex, effectSlot.hasFilter() ? effectSlot.getFilter().getFilterId() : AL_FILTER_NULL);
#endif
        }

        if(stream.hasFilter())
        {
#if !defined(FEA_NO_EFX)
            alSourcei(sourceId, AL_DIRECT_FILTER, stream.getFilter().getFilterId());
#endif
        }

        mStreams.emplace(sourceId, Stream(mPlayingSources.at(handle), stream));
        mStreams.at(sourceId).start();

        std::this_thread::sleep_for(std::chrono::milliseconds(25)); //hack?

        alSourcePlay(sourceId); //play

        return handle;

        return 0;
    }

    void AudioPlayer::pause(AudioHandle handle)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        auto source = mPlayingSources.find(handle);

        if(source != mPlayingSources.end())
        {
            alSourcePause(source->second.getSourceId());
        }
    }

    void AudioPlayer::resume(AudioHandle handle)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        auto source = mPlayingSources.find(handle);

        if(source != mPlayingSources.end())
        {
            alSourcePlay(source->second.getSourceId());
        }
    }

    void AudioPlayer::stop(AudioHandle handle)
    {
        {
            std::lock_guard<std::mutex> lock(mSourcesMutex);
            auto source = mPlayingSources.find(handle);

            if(source != mPlayingSources.end())
            {
                ALuint sourceId = source->second.getSourceId();

                auto streamIterator = mStreams.find(sourceId);
                if(streamIterator != mStreams.end())
                {
                    streamIterator->second.stop();
                }
                alSourceStop(sourceId);
            }
        }
        renewFinishedSources();
    }
    
    size_t AudioPlayer::getMaxSoundsPlaying() const
    {
        return mMaxSoundsPlaying;
    }
    
    void AudioPlayer::setSlotEffect(const AudioEffect& effect, size_t slot)
    {
#if !defined(FEA_NO_EFX)
        FEA_ASSERT(slot < mMaxSoundsPlaying, "Trying to add an effect to slot number " << slot << " but the highest slot number is " << 4 << "!\n");
        alAuxiliaryEffectSloti(mEffectSlots.at(slot).getSlotId(), AL_EFFECTSLOT_EFFECT, effect.getEffectId());
        alAuxiliaryEffectSlotf(mEffectSlots.at(slot).getSlotId(), AL_EFFECTSLOT_GAIN, effect.getEffectGain());
        alAuxiliaryEffectSloti(mEffectSlots.at(slot).getSlotId(), AL_EFFECTSLOT_AUXILIARY_SEND_AUTO, effect.getAutoAdjustments() ? AL_TRUE : AL_FALSE);
#endif
    }

    void AudioPlayer::clearSlotEffect(size_t slot)
    {
#if !defined(FEA_NO_EFX)
        FEA_ASSERT(slot < mMaxSoundsPlaying, "Trying to clear the effects of slot number " << slot << " but the highest slot number is " << 4 << "!\n");
        alAuxiliaryEffectSloti(mEffectSlots.at(slot).getSlotId(), AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
#endif
    }

    void AudioPlayer::setSlotFilter(const AudioFilter& filter, size_t slot)
    {
#if !defined(FEA_NO_EFX)
        FEA_ASSERT(slot < mMaxSoundsPlaying, "Trying to set the filter of slot number " << slot << " but the highest slot number is " << 4 << "!\n");
        mEffectSlots.at(slot).setFilter(filter);
#endif
    }
    
    void AudioPlayer::clearSlotFilter(size_t slot)
    {
#if !defined(FEA_NO_EFX)
        FEA_ASSERT(slot < mMaxSoundsPlaying, "Trying to clear the filter of slot number " << slot << " but the highest slot number is " << 4 << "!\n");
        mEffectSlots.at(slot).clearFilter();
#endif
    }
            
    void AudioPlayer::update()
    {
#if defined(FEA_NO_EFX)
        for(auto& stream : mStreams)
            stream.second.update();
#endif
    }
    
    size_t AudioPlayer::getNumSoundsPlaying() const
    {
        return mNumSoundsPlaying;
    }
    
    PlayStatus AudioPlayer::getStatus(AudioHandle handle) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
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
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set position on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        alSource3f(source.getSourceId(), AL_POSITION, position.x, position.y, position.z);
    }

    Vec3F AudioPlayer::getPosition(AudioHandle handle)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get position of an expired audio!");
        auto& source = mPlayingSources.at(handle);

        Vec3F position;
        alGetSource3f(source.getSourceId(), AL_POSITION, &position.x, &position.y, &position.z);
        return position;
    }

    void AudioPlayer::setVelocity(AudioHandle handle, const Vec3F& velocity) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set velocity on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        alSource3f(source.getSourceId(), AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    }

    Vec3F AudioPlayer::getVelocity(AudioHandle handle)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get velocity of an expired audio!");
        auto& source = mPlayingSources.at(handle);

        Vec3F velocity;
        alGetSource3f(source.getSourceId(), AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
        return velocity;
    }

    void AudioPlayer::setPitch(AudioHandle handle, float pitch) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set pitch on an expired audio!");
        FEA_ASSERT(pitch > 0.0f, "Trying to set pitch to 0 or less! Given " + std::to_string(pitch));
        auto& source = mPlayingSources.at(handle);
        
        alSourcef(source.getSourceId(), AL_PITCH, pitch);
    }

    float AudioPlayer::getPitch(AudioHandle handle)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get pitch on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float pitch;
        alGetSourcef(source.getSourceId(), AL_PITCH, &pitch);
        return pitch;
    }

    void AudioPlayer::setGain(AudioHandle handle, float gain) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set gain on an expired audio!");
        FEA_ASSERT(gain > 0.0f, "Trying to set gain to 0 or less! Given " + std::to_string(gain));
        auto& source = mPlayingSources.at(handle);
        
        alSourcef(source.getSourceId(), AL_GAIN, gain);
    }

    float AudioPlayer::getGain(AudioHandle handle)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get gain on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float gain;
        alGetSourcef(source.getSourceId(), AL_GAIN, &gain);
        return gain;
    }

    void AudioPlayer::setAttenuationFactor(AudioHandle handle, float attenuationFactor)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set attenuation factor on an expired audio!");
        FEA_ASSERT(attenuationFactor > 0.0f, "Trying to set attenuation factor to 0 or less! Given " + std::to_string(attenuationFactor));
        auto& source = mPlayingSources.at(handle);

        alSourcef(source.getSourceId(), AL_ROLLOFF_FACTOR, attenuationFactor);
    }

    float AudioPlayer::getAttenuationFactor(AudioHandle handle) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get attenuation factor on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float attenuationFactor;
        alGetSourcef(source.getSourceId(), AL_ROLLOFF_FACTOR, &attenuationFactor);
        return attenuationFactor;
    }

    void AudioPlayer::setAttenuationDistance(AudioHandle handle, float attenuationDistance)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set attenuation distance on an expired audio!");
        FEA_ASSERT(attenuationDistance > 0.0f, "Trying to set attenuation factor to 0 or less! Given " + std::to_string(attenuationDistance));
        auto& source = mPlayingSources.at(handle);

        alSourcef(source.getSourceId(), AL_REFERENCE_DISTANCE, attenuationDistance);
    }

    float AudioPlayer::getAttenuationDistance(AudioHandle handle) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get attenuation distance on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        float attenuationDistance;
        alGetSourcef(source.getSourceId(), AL_REFERENCE_DISTANCE, &attenuationDistance);
        return attenuationDistance;
    }

    void AudioPlayer::setLooping(AudioHandle handle, bool looping)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set looping on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        alSourcei(source.getSourceId(), AL_LOOPING, looping? AL_TRUE : AL_FALSE);
    }

    bool AudioPlayer::isLooping(AudioHandle handle) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get looping on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        ALint looping;
        alGetSourcei(source.getSourceId(), AL_LOOPING, &looping);
        return looping == AL_TRUE? true : false;
    }

    void AudioPlayer::setRelative(AudioHandle handle, bool relative)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to set relative on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        alSourcei(source.getSourceId(), AL_SOURCE_RELATIVE, relative? AL_TRUE : AL_FALSE);
    }

    bool AudioPlayer::isRelative(AudioHandle handle) const
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        FEA_ASSERT(mPlayingSources.find(handle) != mPlayingSources.end(), "Trying to get relative on an expired audio!");
        auto& source = mPlayingSources.at(handle);

        ALint relative;
        alGetSourcei(source.getSourceId(), AL_SOURCE_RELATIVE, &relative);
        return relative == AL_TRUE? true : false;
    }

    void AudioPlayer::setListener(const Listener& listener)
    {
        mListener = listener;
        const Vec3F& at = listener.getOrientationAt();
        const Vec3F& up = listener.getOrientationUp();
        float orientation[] = {at.x, at.y, at.z, up.x, up.y, up.z};
        alListenerfv(AL_ORIENTATION, orientation);
    }

    const Listener& AudioPlayer::getListener() const
    {
        return mListener;
    }
    
    size_t AudioPlayer::getMaxAuxiliarySend() const
    {
        return mMaxAuxSend;
    }
    
    void AudioPlayer::setupSources(size_t maxSoundAmount)
    {
        for(size_t i = 0; i < maxSoundAmount; i++)
            mIdleSources.push(PlaySource());
    }
    
    void AudioPlayer::renewFinishedSources()
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        
        for(auto sourceIterator = mPlayingSources.begin(); sourceIterator != mPlayingSources.end();)
        {
            ALint state;
            ALuint sourceId = sourceIterator->second.getSourceId();
            alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
            if(state == AL_STOPPED)
            {
                alSourcei(sourceId, AL_BUFFER, AL_NONE);
                mIdleSources.push(std::move(sourceIterator->second));
                sourceIterator = mPlayingSources.erase(sourceIterator);
                mNumSoundsPlaying--;

                auto iterator = mStreams.find(sourceId);
                if(iterator != mStreams.end())
                {
#if !defined(FEA_NO_EFX)
                    if(iterator->second.isRunning())
                        iterator->second.stop();
#else
#endif

                    mStreams.erase(iterator);
                }
            }
            else
            {
                sourceIterator++;
            }
        }
    }
    
#if !defined(FEA_NO_EFX)
    AudioPlayer::Stream::Stream(const PlaySource& source, AudioStream& audioStream) : 
        mSource(source),
        mStream(audioStream),
        mIsFinishing(false)
    {
    }

    AudioPlayer::Stream::Stream(Stream&& other) :
        mSource(std::move(other.mSource)),
        mStream(other.mStream),
        mIsFinishing(other.mIsFinishing),
        mStreamerThread(std::move(other.mStreamerThread))
    {
    }

    void AudioPlayer::Stream::streamerThread()
    {
        while(!mIsFinishing)
        {
            ALint buffersProcessed;
            alGetSourcei(mSource.getSourceId(), AL_BUFFERS_PROCESSED, &buffersProcessed);

            if(buffersProcessed > 0)
            {
                ALuint bufferId = mQueued.front();
                mQueued.pop();
                alSourceUnqueueBuffers(mSource.getSourceId(), 1, &bufferId);
                mStream.bufferConsumed();
            }

            while(AudioBuffer* newBuffer = mStream.nextReadyBuffer())
            {
                ALuint bufferId = newBuffer->getBufferId();
                alSourceQueueBuffers(mSource.getSourceId(), 1, &bufferId);
                mQueued.push(bufferId);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    }
    
    void AudioPlayer::Stream::start()
    {
        mRunning = true;
        mStreamerThread = std::thread(&Stream::streamerThread, this);
    }
    
    void AudioPlayer::Stream::stop()
    {
        mRunning = false;
        alSourceStop(mSource.getSourceId());
        while(mQueued.size())
        {
            uint32_t bufferId = mQueued.front();
            mQueued.pop();
            alSourceUnqueueBuffers(mSource.getSourceId(), 1, &bufferId);
        }

        if(mStreamerThread.joinable())
        {
            mIsFinishing = true;
            mStreamerThread.join();
        }
    }

    bool AudioPlayer::Stream::isRunning()
    {
        return mRunning;
    }
#else
    AudioPlayer::Stream::Stream(const PlaySource& source, AudioStream& audioStream) : 
        mSource(source),
        mStream(audioStream)
    {
    }

    AudioPlayer::Stream::Stream(Stream&& other) :
        mSource(std::move(other.mSource)),
        mStream(other.mStream)
    {
    }

    void AudioPlayer::Stream::start()
    {
        while(AudioBuffer* newBuffer = mStream.nextReadyBuffer())
        {
            ALuint bufferId = newBuffer->getBufferId();
            mQueued.push(bufferId);
            alSourceQueueBuffers(mSource.getSourceId(), 1, &bufferId);
        }
    }

    void AudioPlayer::Stream::update()
    {
        ALint buffersProcessed;
        alGetSourcei(mSource.getSourceId(), AL_BUFFERS_PROCESSED, &buffersProcessed);
        if(buffersProcessed > 0)
        {
            ALuint bufferId = mQueued.front();
            mQueued.pop();
            alSourceUnqueueBuffers(mSource.getSourceId(), 1, &bufferId);
            mStream.bufferConsumed();
        }

        while(AudioBuffer* newBuffer = mStream.nextReadyBuffer())
        {
            ALuint bufferId = newBuffer->getBufferId();
            mQueued.push(bufferId);
            alSourceQueueBuffers(mSource.getSourceId(), 1, &bufferId);
        }
    }
    
    void AudioPlayer::Stream::stop()
    {
        alSourceStop(mSource.getSourceId());
        while(mQueued.size() > 0)
        {
            ALuint bufferId = mQueued.front();
            mQueued.pop();
            alSourceUnqueueBuffers(mSource.getSourceId(), 1, &bufferId);
        }
    }
#endif
}
