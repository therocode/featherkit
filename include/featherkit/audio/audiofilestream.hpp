#pragma once
#include <featherkit/audio/audiostream.hpp>
#include <featherkit/audio/audiofile.hpp>

namespace fea
{
    class AudioFileStream : public AudioStream
    {
        public:
            AudioFileStream();
            virtual AudioData fetchBufferData(size_t bufferIndex) override;
            void setFile(AudioFile& file);
        private:
            AudioFile* mFile;
            size_t mBufferSize;
    };
}
