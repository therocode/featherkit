#pragma once
#include <featherkit/audio/audiostream.hpp>
#include <featherkit/audio/audiofile.hpp>

namespace fea
{
    class AudioFileStream : public AudioStream
    {
        public:
            AudioFileStream();
            virtual void fillBufferData(size_t bufferIndex, AudioData& toFill) override;
            void setFile(AudioFile& file);
        private:
            AudioFile* mFile;
            size_t mBufferSize;
    };
}
