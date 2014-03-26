#pragma once
#include <sndfile.h>
#include <string>
#include <vector>

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
            std::vector<int16_t> getSampleData() const;
            void open(const std::string& path);
            SNDFILE* getInternal(); //provide API for this
        private:
            SNDFILE* mFile;
            int32_t mChannelCount;
            int32_t mSampleRate;
            size_t mSampleAmount;
    };
}
