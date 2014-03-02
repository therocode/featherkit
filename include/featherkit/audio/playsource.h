#pragma once
#include <al.h>
#include <cstring>

namespace fea
{
    class PlaySource
    {
        public:
            PlaySource();
            ~PlaySource();
            ALuint getSourceId() const;
        private:
            ALuint mSourceId;
    };
}
