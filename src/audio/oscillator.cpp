#include <featherkit/audio/oscillator.hpp>
#include <limits>
#include <cmath>
#include <iostream>

const double pi = 3.14159;

namespace fea
{
    Oscillator::Oscillator() :
        mFrequency(440.0f),
        mTheta(0.0)
    {
        setStreamProperties(1, 48000);
        reset();
    }

    void Oscillator::fillBufferData(size_t bufferIndex, AudioData& toFill)
    {
        size_t sampleAmount = toFill.mSamples.size();

        double deltaTheta = 2.0 * pi * ((double)mFrequency / (double)getSampleRate());

        for(int i = 0; i < sampleAmount; i++)
        {
            toFill.mSamples[i] = (int16_t) (std::numeric_limits<int16_t>::max() * sin(mTheta));
            //data.get()[i] = rand() % (std::numeric_limits<int16_t>::max() * 2) - std::numeric_limits<int16_t>::max();
            mTheta += deltaTheta;

            if(mTheta > 2.0 * pi) 
                mTheta = mTheta - 2.0 * pi;
        }

        toFill.mSampleAmount = sampleAmount;
    }

    void Oscillator::setFrequency(float frequency)
    {
        mFrequency = frequency;
        reset();
    }
}
