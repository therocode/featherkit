#pragma once
#include <al.h>
#include <cstring>

namespace fea
{
    class PlaySource
    {
        public:
            PlaySource();
            PlaySource(const PlaySource& other) = delete;
            PlaySource(PlaySource&& other);
            ~PlaySource();
            PlaySource& operator=(const PlaySource& other) = delete; 
            PlaySource& operator=(PlaySource&& other); 
            ALuint getSourceId() const;
        private:
            ALuint mSourceId;
    };
}
