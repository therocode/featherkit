#pragma once
#include <vector>
#include <memory>
#include <featherkit/audio/audiobuffer.hpp>

namespace fea
{
    using AudioBufferList = std::vector<std::unique_ptr<fea::AudioBuffer>>;

    class AudioSource
    {
        public:
            const AudioBufferList& getBuffers() const;
        protected:
            AudioBufferList mBuffers;
    };
}
