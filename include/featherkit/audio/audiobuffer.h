#pragma once
#include <al.h>
#include <cstring>

namespace fea
{
    class AudioBuffer
    {
        public:
            AudioBuffer();
            ~AudioBuffer();
            ALuint getBufferId() const;
        private:
            ALuint mBufferId;
            size_t mDataSize;
    };
}
