#pragma once
#include <fea/config.hpp>
#include <vector>
#include <queue>
#include <cstring>
#include <fea/audio/audiobuffer.hpp>
#include <fea/audio/audiobase.hpp>
#include <memory>

namespace fea
{
    class FEA_API AudioStream : public AudioBase
    {
        public:
            AudioStream();
            AudioStream(size_t bufferAmount, size_t bufferSize);
            void setStreamProperties(size_t channelCount, size_t sampleRate);
            AudioBuffer* nextReadyBuffer();
            void bufferConsumed();
            virtual void fillBufferData(size_t sampleIndex, std::vector<int16_t>& toFill) = 0;
            size_t getSampleRate() const;
            size_t getChannelCount() const;
            void setPlayOffset(std::chrono::milliseconds timePoint);
        protected:
            void reset();
        private:
            size_t mChannelCount;
            size_t fillBuffer(AudioBuffer* buffer);
            std::vector<std::shared_ptr<AudioBuffer>> mBuffers;
            size_t mBufferSize;
            std::queue<size_t> mReadyBuffers;
            std::queue<size_t> mConsumingBuffers;
            size_t mCurrentSample;
            ALenum mFormat;
            size_t mSampleRate;
    };
    /** @addtogroup Audio
     *@{
     *  @class AudioStream
     *@}
     ***
     *  @class AudioStream
     *  @brief Base class for any type of audio that is streamed.
     *
     *  Audio streams are designed after the principle of only keeping a small amount of tiny buffers for storing audio data. These are filled over time by the stream from another medium such as a file, network or just procedurally generated. These buffers are filled over time by the system calling the fillBufferData function.
     *
     *  To create a stream, this class must be inherited and the fillBufferData function has to be implemented which should define how the stream provides sample data. The setStreamProperties function must also be called before usage.
     ***
     *  @fn AudioStream::AudioStream()
     *  @brief Construct an AudioStream.
     *
     *  This makes the stream have 3 buffers with 48000 as the size.
     ***
     *  @fn AudioStream::AudioStream(size_t bufferAmount, size_t bufferSize)
     *  @brief Create an AudioStream with a custom amount of buffers and buffer size.
     ***
     *  @fn void AudioStream::setStreamProperties(size_t channelCount, size_t sampleRate)
     *  @brief Set the channel count and sample rate of the stream.
     *
     *  This has to be called to set up the stream properly before use.
     *  @param channelCount Amount of audio channels in the stream data.
     *  @param sampleRate Sample rate of the stream data.
     ***
     *  @fn AudioBuffer* AudioStream::nextReadyBuffer()
     *  @brief Get the next filled buffer.
     *
     *  This is called by the AudioPlayer to fetch the audio data which needs to be played.
     *  @return Buffer with the audio data. Will be null if there are no filled buffers to fetch.
     ***
     *  @fn void AudioStream::bufferConsumed()
     *  @brief Tell the stream that a buffer has been consumed.
     *
     *  This is called by the AudioPlayer when a buffer has been fully played to tell the stream to generate more data. This will result in a call to fillBufferData with the correct sample index.
     ***
     *  @fn virtual void AudioStream::fillBufferData(size_t sampleIndex, std::vector<int16_t>& toFill) = 0
     *  @brief Fill a buffer with stream data.
     *
     *  This function should be implemented by all streams to define how they fill buffer data. It will be called when it is necessary to fill the next buffer. If there is no more data in the stream and playback should stop, toFill should be set to an empty vector.
     *  @param sampleIndex Index of the sample to fill from.
     *  @param toFill Vector to fill the data into. This vector is resized to fit the amount of data expected and should not be increased in size using push_back for instance. Instead loop through the entries and set the data directly. If there is less data remaining in the stream than the vector can fit, the vector must me resized to a smaller size, fitting the data. If no data is available, running toFill.clear() or toFill.resize(0) is sufficient and playback will then stop.
     ***
     *  @fn size_t AudioStream::getSampleRate() const
     *  @brief Get the sample rate of the stream.
     *  @return The sample rate.
     ***
     *  @fn size_t AudioStream::getChannelCount() const
     *  @brief Get the amount of channels.
     *  @return The amount of channels.
     ***
     *  @fn void AudioStream::setPlayOffset(std::chrono::milliseconds timePoint)
     *  @brief Set the play offset.
     *
     *  When the play offset is set, the stream will request the buffers to be filled at the corresponding sample index based on the time.
     *  @param timePoint Time to set the play offset to.
     ***
     *  @fn void AudioStream::reset()
     *  @brief Reset the stream to its initial state.
     *
     *  This can be used when making a stream class as a form of initializer which sets the stream to a starting state.
     ***/
}
