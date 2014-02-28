#include <featherkit/audio/audio.h>

namespace fea
{
        Audio::Audio() : mPitch(1.0f),
                         mSource(nullptr)
        {
        }

        void Audio::setPitch(float pitch)
        {
            mPitch = pitch;
        }

        float Audio::getPitch() const
        {
            return mPitch;
        }

        void Audio::setSource(AudioSource& source)
        {
            mSource = &source;
        }
}
