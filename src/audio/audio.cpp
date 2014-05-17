#include <fea/audio/audio.hpp>
#include <fea/assert.hpp>

namespace fea
{
        Audio::Audio() : 
            mSample(nullptr)
        {
        }

        void Audio::setSample(AudioSample& sample)
        {
            mSample = &sample;
        }

        const AudioSample& Audio::getSample() const
        {
            FEA_ASSERT(mSample != nullptr, "Trying to access the sample from an audio instance which has no sample set!");
            return *mSample;
        }
            
        bool Audio::hasSample() const
        {
            return mSample != nullptr;
        }
}
