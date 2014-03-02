#include <featherkit/audio/audiosample.h>
#include <featherkit/audio/audiofile.h>

namespace fea
{
    void AudioSample::loadSampleData(const AudioFile& audioFile)
    {
        AudioData sampleData = audioFile.getSampleData();

        alBufferData(mBuffers[0]->getBufferId(), audioFile.getFormat(), sampleData.mData.get(), sampleData.mDataAmount, audioFile.getFrequency());
    }
}
