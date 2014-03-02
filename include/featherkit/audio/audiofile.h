#pragma once
#include <featherkit/audio/audiodata.h>
#include <sndfile.h>
#include <al.h>

namespace fea
{
    class AudioFile
    {
        public:
            ALenum getFormat() const;
            ALint getFrequency() const;
            AudioData getSampleData() const;
            void open(const std::string& path);
    };
}
