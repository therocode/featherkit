#pragma once
#include <vector>
#include <memory>
#include <featherkit/audio/audiobuffer.h>

namespace fea
{
    using AudioBufferList = std::vector<std::unique_ptr<fea::AudioBuffer>>;

    class AudioSource
    {
        public:
            const AudioBufferList& getBuffers() const;
        private:
            AudioBufferList mBuffers;
    };
}
