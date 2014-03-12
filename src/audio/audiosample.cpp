#include <featherkit/audio/audiosample.hpp>
#include <featherkit/audio/audiofile.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    void AudioSample::loadSampleData(const AudioFile& audioFile)
    {
        AudioData sampleData = audioFile.getSampleData();
        FEA_ASSERT(sampleData.mSampleAmount > 0, "Trying to load samples from a file containing no samples!");

        if(!mBuffer)
            mBuffer = std::unique_ptr<AudioBuffer>(new AudioBuffer());

        ALint format;
        
        switch(audioFile.getChannelCount())
        {
            case 1  : format = AL_FORMAT_MONO16;                    break;
            case 2  : format = AL_FORMAT_STEREO16;                  break;
            case 4  : format = alGetEnumValue("AL_FORMAT_QUAD16");  break;
            case 6  : format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
            case 7  : format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
            case 8  : format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
            default : format = 0;                                   break;
        }

        // Fixes a bug on OS X supposedly
        if (format == -1)
            format = 0;

        alBufferData(mBuffer->getBufferId(), format, sampleData.mSamples.data(), sampleData.mSampleAmount * sizeof(int16_t), audioFile.getSampleRate());
    }
    
    const AudioBuffer& AudioSample::getBuffer() const
    {
        return *mBuffer;
    }
}
