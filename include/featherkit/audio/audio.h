#pragma once

namespace fea
{
    class AudioSource;

    class Audio
    {
        public:
            Audio();
            void setPitch(float pitch);
            float getPitch() const;
            void setSource(AudioSource& source);
            const AudioSource& getSource() const;
        private:
            float mPitch;
            AudioSource* mSource;
    };
}
