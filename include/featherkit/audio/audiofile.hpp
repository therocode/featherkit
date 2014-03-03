#pragma once
#include <featherkit/audio/audiodata.hpp>
#include <sndfile.h>
#include <al.h>

namespace fea
{
    class AudioFile
    {
        public:
            AudioFile();
            AudioFile(const AudioFile& other) = delete;
            AudioFile(AudioFile&& other);
            ~AudioFile();
            AudioFile& operator=(const AudioFile& other) = delete; 
            AudioFile& operator=(AudioFile&& other); 
            ALenum getFormat() const;
            ALint getSampleRate() const;
            AudioData getSampleData() const;
            void open(const std::string& path);
        private:
            SNDFILE* mFile;
            ALenum mFormat;
            ALint mSampleRate;
            size_t mSampleAmount;
    };
}
