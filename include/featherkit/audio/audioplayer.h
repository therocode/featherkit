#pragma once
#include <al.h>
#include <alc.h>
#include <stack>
#include <unordered_map>
#include <featherkit/audio/playsource.h>
#include <thread>
#include <mutex>

namespace fea
{
    using AudioHandle = size_t;
    class Audio;

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
        private:
            void setupSources(size_t maxSoundAmount);
            void renewerThread();
            void renewFinishedSources();
            ALCdevice*  mAudioDevice;
            ALCcontext* mAudioContext;
            std::stack<PlaySource> mSources;
            const size_t mMaxSoundsPlaying;
            size_t mNumSoundsPlaying;
            AudioHandle mNextHandle;
            std::unordered_map<AudioHandle, PlaySource> mPlayingSources;

            std::thread mRenewer;
            std::mutex mSourcesMutex;
            bool mRenewSources;
    };
}
