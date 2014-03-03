#include <featherkit/audio/audio.h>

namespace fea
{
        Audio::Audio() : mPosition({0.0f, 0.0f, 0.0f}),
                         mPitch(1.0f),
                         mSource(nullptr)
        {
        }

        void Audio::setPosition(const Vec3F& position)
        {
            mPosition = position;
        }

        const Vec3F& Audio::getPosition() const
        {
            return mPosition;
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
        
        const AudioSource& Audio::getSource() const
        {
            return *mSource;
        }
}
