#pragma once
#include <al.h>
#include <alc.h>
#include <stack>
#include <unordered_map>
#include <featherkit/audio/playsource.h>
#include <featherkit/audio/vec3f.h>
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
            void setPitch(AudioHandle handle, float pitch) const;
            float getPitch(AudioHandle handle);
        private:
            void setupSources(size_t maxSoundAmount);
            void renewerThread();
            void renewFinishedSources();
            ALCdevice*  mAudioDevice;
            ALCcontext* mAudioContext;
            std::stack<PlaySource> mIdleSources;
            const size_t mMaxSoundsPlaying;
            size_t mNumSoundsPlaying;

            AudioHandle mNextHandle;
            std::unordered_map<AudioHandle, PlaySource> mPlayingSources;
            std::thread mRenewer;
            std::mutex mSourcesMutex;
            bool mRenewSources;
    };
}
