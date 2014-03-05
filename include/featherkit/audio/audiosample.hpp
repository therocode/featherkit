#pragma once
#include <memory>
#include <featherkit/audio/audiobuffer.hpp>

namespace fea
{
    class AudioFile;

    class AudioSample
    {
        public:
            void loadSampleData(const AudioFile& audioFile);
            const AudioBuffer& getBuffer() const;
        private:
            std::unique_ptr<AudioBuffer> mBuffer;
    };
}
