#pragma once
#include <featherkit/audio/audiodata.hpp>
#include <sndfile.h>

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
            int32_t getChannelCount() const;
            int32_t getSampleRate() const;
            AudioData getSampleData() const;
            void open(const std::string& path);
            SNDFILE* getInternal(); //provide API for this
        private:
            SNDFILE* mFile;
            int32_t mChannelCount;
            int32_t mSampleRate;
            size_t mSampleAmount;
    };
}
