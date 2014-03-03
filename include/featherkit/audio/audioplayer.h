#pragma once
#include <al.h>
#include <alc.h>
#include <stack>
#include <unordered_map>
#include <featherkit/audio/playsource.h>
#include <featherkit/audio/listener.h>
#include <thread>
#include <mutex>

namespace fea
{
    using AudioHandle = size_t;
    class Audio;

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
            bool getLooping(AudioHandle handle) const;
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

            AudioHandle mNextHandle;
            std::unordered_map<AudioHandle, PlaySource> mPlayingSources;
            std::thread mRenewer;
            std::mutex mSourcesMutex;
            bool mRenewSources;
    };
}
