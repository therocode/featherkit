#pragma once
#include <al.h>
#include <alc.h>
#include <stack>
#include <unordered_map>
#include <featherkit/audio/playsource.hpp>
#include <featherkit/audio/listener.hpp>
#include <featherkit/audio/effectslot.hpp>
#include <featherkit/audio/audioeffect.hpp>
#include <featherkit/audio/audiofilter.hpp>
#include <thread>
#include <mutex>
#include <vector>

namespace fea
{
    using AudioHandle = size_t;
    class Audio;
    class AudioStream;

    enum PlayStatus {PLAYING, PAUSED, EXPIRED};

    class AudioPlayer
    {
        public:
            AudioPlayer();
            AudioPlayer(const AudioPlayer& other) = delete;
            AudioPlayer(AudioPlayer&& other) = delete;
            AudioPlayer& operator=(const AudioPlayer& other) = delete;
            AudioPlayer& operator=(AudioPlayer&& other) = delete;
            ~AudioPlayer();
            AudioHandle play(Audio& audio);
            AudioHandle play(AudioStream& stream);
            void pause(AudioHandle handle);
            void resume(AudioHandle handle);
            void stop(AudioHandle handle);
            size_t getMaxSoundsPlaying() const;
            size_t getNumSoundsPlaying() const;
            PlayStatus getStatus(AudioHandle handle) const;
            void setPosition(AudioHandle handle, const Vec3F& position) const;
            Vec3F getPosition(AudioHandle handle);
            void setVelocity(AudioHandle handle, const Vec3F& velocity) const;
            Vec3F getVelocity(AudioHandle handle);
            void setPitch(AudioHandle handle, float pitch) const;
            float getPitch(AudioHandle handle);
            void setGain(AudioHandle handle, float gain) const;
            float getGain(AudioHandle handle);
            void setAttenuationFactor(AudioHandle handle, float attenuationFactor);
            float getAttenuationFactor(AudioHandle handle) const;
            void setAttenuationDistance(AudioHandle handle, float attenuationDistance);
            float getAttenuationDistance(AudioHandle handle) const;
            void setLooping(AudioHandle handle, bool looping);
            bool isLooping(AudioHandle handle) const;
            void setRelative(AudioHandle handle, bool relative);
            bool isRelative(AudioHandle handle) const;
            void setListener(const Listener& listener);
            const Listener& getListener() const;
            size_t getMaxAuxiliarySend() const;
            void addEffectToSlot(const AudioEffect& effect, size_t slot);
            void clearSlotEffects(size_t slot);
            void setSlotFilter(const AudioFilter& filter, size_t slot);
            void clearSlotFilter(size_t slot);
        private:
            void setupSources(size_t maxSoundAmount);
            void renewerThread();
            void renewFinishedSources();
            ALCdevice*  mAudioDevice;
            ALCcontext* mAudioContext;
            ALCint mMaxAuxSend;
            std::stack<PlaySource> mIdleSources;
            const size_t mMaxSoundsPlaying;
            size_t mNumSoundsPlaying;
            Listener mListener;

            //recycle sources
            AudioHandle mNextHandle;
            std::unordered_map<AudioHandle, PlaySource> mPlayingSources;
            mutable std::mutex mSourcesMutex;
            bool mRenewSources;
            std::thread mRenewer;

            //streaming threads
            class Stream
            {
                public:
                    Stream(const PlaySource& source, AudioStream& audioStream);
                    void streamerThread();
                    void start();
                    void stop();
                private:
                    const PlaySource& mSource;
                    AudioStream& mStream;
                    bool mIsFinishing;
                    std::thread mStreamerThread;
            };

            std::unordered_map<ALuint, Stream> mStreams;

            //effect stuff
            std::vector<EffectSlot> mEffectSlots;
    };
}
