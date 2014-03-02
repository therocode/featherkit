#include <featherkit/audio/audiosample.h>
#include <featherkit/audio/audiofile.h>
#include <featherkit/assert.h>

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
