#pragma once
#include <al.h>
#include <alc.h>

namespace fea
{
    class Audio;

    class AudioPlayer
    {
        public:
            AudioPlayer();
            ~AudioPlayer();
            void play(Audio& audio);
        private:
             ALCdevice*  mAudioDevice;
             ALCcontext* mAudioContext;
    };
}
