#pragma once
#include <vector>
#include <queue>
#include <cstring>
#include <featherkit/audio/audiobuffer.hpp>
#include <featherkit/audio/audiodata.hpp>

namespace fea
{
    class AudioStream
    {
        public:
            AudioStream();
            AudioStream(size_t bufferAmount);
            void setStreamProperties(size_t channelCount, size_t sampleRate);
            AudioBuffer* nextReadyBuffer();
            void bufferConsumed();
            virtual void fillBufferData(size_t bufferIndex, AudioData& toFill) = 0;
            size_t getSampleRate() const;
        protected:
            size_t fillBuffer(AudioBuffer* buffer);
            void reset();
            size_t mChannelCount;
        private:
            std::vector<AudioBuffer> mBuffers;
            std::queue<size_t> mReadyBuffers;
            std::queue<size_t> mConsumingBuffers;
            size_t mNextToFill;
            ALenum mFormat;
            size_t mSampleRate;
    };
}
