#pragma once
#include <fea/config.hpp>
#include <fea/audio/openal.hpp>
#include <cstring>

namespace fea
{
    class FEA_API AudioBuffer
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
