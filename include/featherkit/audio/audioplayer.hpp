#pragma once
#include <al.h>
#include <alc.h>
#include <stack>
#include <unordered_map>
#include <featherkit/audio/playsource.hpp>
#include <featherkit/audio/listener.hpp>
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
        private:
            void setupSources(size_t maxSoundAmount);
            void renewerThread();
            void renewFinishedSources();
            ALCdevice*  mAudioDevice;
            ALCcontext* mAudioContext;
            std::stack<PlaySource> mIdleSources;
            const size_t mMaxSoundsPlaying;
            size_t mNumSoundsPlaying;
            Listener mListener;

            //recycle sources
            AudioHandle mNextHandle;
            std::unordered_map<AudioHandle, PlaySource> mPlayingSources;
            std::mutex mSourcesMutex;
            bool mRenewSources;
            std::thread mRenewer;

            //streaming threads
            class Stream
            {
                public:
                    Stream(const PlaySource& source, AudioStream& audioStream);
                    bool isFinished() const;
                    void streamerThread();
                    void start();
                private:
                    const PlaySource& mSource;
                    AudioStream& mStream;
                    bool mIsFinished;
                    std::thread mStreamerThread;
            };

            std::vector<Stream> mStreams;
    };
}
