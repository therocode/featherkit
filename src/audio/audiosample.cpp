#include <featherkit/audio/audiosample.hpp>
#include <featherkit/audio/audiofile.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    void AudioSample::loadSampleData(const AudioFile& audioFile)
    {
        AudioData sampleData = audioFile.getSampleData();
        FEA_ASSERT(sampleData.mDataAmount > 0, "Trying to load samples from a file containing no samples!");

        if(mBuffers.size() == 0)
            mBuffers.push_back(std::unique_ptr<AudioBuffer>(new AudioBuffer()));


        alBufferData(mBuffers[0]->getBufferId(), audioFile.getFormat(), sampleData.mData.get(), sampleData.mDataAmount, audioFile.getSampleRate());

    }
}
