#pragma once
#include <fea/config.hpp>
#include <fea/audio/openal.hpp>
#include <cstring>

namespace fea
{
    class FEA_API PlaySource
    {
        public:
            PlaySource();
            PlaySource(const PlaySource& other) = delete;
            PlaySource(PlaySource&& other);
            PlaySource& operator=(const PlaySource& other) = delete; 
            PlaySource& operator=(PlaySource&& other); 
            ~PlaySource();
            ALuint getSourceId() const;
        private:
            ALuint mSourceId;
    };
}
