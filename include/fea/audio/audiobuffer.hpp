#pragma once
#include "al.h"
#include <cstring>

namespace fea
{
    class AudioBuffer
    {
        public:
            AudioBuffer();
            AudioBuffer(const AudioBuffer& other) = delete;
            AudioBuffer(AudioBuffer&& other);
            AudioBuffer& operator=(const AudioBuffer& other) = delete; 
            AudioBuffer& operator=(AudioBuffer&& other); 
            ~AudioBuffer();
            ALuint getBufferId() const;
        private:
            ALuint mBufferId;
            size_t mDataSize;
    };
}
